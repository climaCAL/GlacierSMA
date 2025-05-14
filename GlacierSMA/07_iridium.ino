// Configure RockBLOCK 9603
void configureIridium()
{
  modem.setPowerProfile(IridiumSBD::USB_POWER_PROFILE);     // Assume low power (Battery power: IridiumSBD::DEFAULT_POWER_PROFILE)
  modem.adjustSendReceiveTimeout(iridiumTimeout);           // Timeout for Iridium send/receive commands (default = 300 s)
  modem.adjustStartupTimeout(iridiumTimeout / 2);           // Timeout for Iridium startup (default = 240 s)
}

void addMoSbdMessage() {
  moSbdMessage.iterationCounter = ++iterationCounter; // Write message counter data to union

  // Copy MO-SBD message structure to message buffer
  if (!messageBuffer.push(moSbdMessage)) {
    DEBUG_PRINT("Warning - Message dropped because buffer is full ("); DEBUG_PRINT(messageBuffer.size()); DEBUG_PRINTLN(" messages pending)");
  }

  // Print MO-SBD union/structure
  printMoSbd();
  //printMoSbdHex();

  // Clear MO-SBD message union/structure
  memset(&moSbdMessage, 0x00, sizeof(moSbdMessage));
}

// Write data from structure to transmit buffer
size_t writeMoSbdBuffer() {
  for (transmitCounter = 0; transmitCounter < messageBuffer.size() && transmitCounter < transmitLimit; transmitCounter++) {
    SBD_MO_MESSAGE msg = messageBuffer[transmitCounter];
    memcpy(moSbdBuffer + transmitCounter * sizeof(msg), msg.bytes, sizeof(msg));
  }
  //printMoSbdBuffer();
  return transmitCounter * sizeof(SBD_MO_MESSAGE);
}

// Attempt to transmit data via RockBLOCK 9603
void transmitData() {
  // Start loop timer
  unsigned long loopStartTime = millis();

  // Enable power to the RockBLOCK 9603
  enable5V();

  // Open the Iridium serial port
  IRIDIUM_PORT.begin(19200);

  // Assign pins for SERCOM functionality for new Serial2 instance
  pinPeripheral(PIN_IRIDIUM_TX, PIO_SERCOM);
  pinPeripheral(PIN_IRIDIUM_RX, PIO_SERCOM);

  // Wake up the RockBLOCK 9603 and begin communications
  DEBUG_PRINT("Info - Starting iridium modem ("); DEBUG_PRINT(iridiumTimeout/2); DEBUG_PRINTLN("s)...");
  petDog(); // The following might take a while, so best reset the WDT here
  int returnCode = modem.begin();

  if (NO_TRANSMIT)
  {
    DEBUG_PRINTLN("Info - Satellite messages inhibited (#NO_TRANSMIT)");
    DEBUG_PRINTLN("Waiting 60s for capacitors to charge...");
    myDelay(60000);
    online.iridium = false;
  }
  else if (returnCode != ISBD_SUCCESS)
  {
    online.iridium = false;
    if (returnCode == ISBD_NO_MODEM_DETECTED)
    {
      DEBUG_PRINTLN("Warning - No modem detected! Please check wiring.");
    }
    else
    {
      DEBUG_PRINT("Warning - Modem begin failed with error "); DEBUG_PRINTLN(returnCode);
    }
  }
  else
  {
    online.iridium = true;

    // Calculate SBD message buffer sizes
    moSbdBufferSize = writeMoSbdBuffer(); // Write data to transmit buffer
    mtSbdBufferSize = sizeof(mtSbdBuffer);
    memset(mtSbdBuffer, 0x00, sizeof(mtSbdBuffer)); // Clear MT-SBD buffer

    DEBUG_PRINT("Info - Attempting to transmit message ("); DEBUG_PRINT(iridiumTimeout); DEBUG_PRINTLN("s)...");
    petDog(); // The following might take a while, so best reset the WDT here

    // Transmit and receive SBD message data in binary format
    returnCode = modem.sendReceiveSBDBinary(moSbdBuffer, moSbdBufferSize, mtSbdBuffer, mtSbdBufferSize);

    // Check if transmission was successful
    if (returnCode == ISBD_SUCCESS)
    {
      DEBUG_PRINTLN("Info - MO-SBD message transmission successful!");
      blinkLed(PIN_LED_GREEN, 10, 500);

      failureCounter = 0; // Clear failed transmission counter
      memset(moSbdBuffer, 0x00, sizeof(moSbdBuffer)); // Clear MO-SBD message buffer

      while (messageBuffer.size() > 0 && transmitCounter-- > 0) // Remove sent messages from buffer
        messageBuffer.shift();

      // Check if a Mobile Terminated (MT) SBD message was received
      // If no message is available, mtSbdBufferSize = 0
      if (mtSbdBufferSize > 0)
      {
        DEBUG_PRINT("Info - MT-SBD message received. Size: ");
        DEBUG_PRINT(mtSbdBufferSize); DEBUG_PRINTLN(" bytes.");

        // Check if MT-SBD message is the correct size
        if (mtSbdBufferSize >= sizeof(mtSbdMessage))
        {
          DEBUG_PRINT("Info - MT-SBD message received. Size: ");
          DEBUG_PRINT(mtSbdBufferSize); DEBUG_PRINTLN(" bytes.");
          printMtSbdBuffer(); // Print MT-SBD message in hexadecimal
          // Write incoming MT-SBD message to union/structure
          memcpy(mtSbdMessage.bytes, mtSbdBuffer, sizeof(mtSbdMessage));

          // Print MT-SBD message
          printMtSbd(); // Print MT-SBD message stored in union/structure

          // Check if MT-SBD message data is valid and update variables
          if ((mtSbdMessage.sampleInterval    >= 1  &&  mtSbdMessage.sampleInterval   <= 60)  &&
              (mtSbdMessage.averageInterval   >= 1  &&  mtSbdMessage.averageInterval  <= 240)  &&
              (mtSbdMessage.transmitInterval  >= 1  &&  mtSbdMessage.transmitInterval <= 24)  &&
              (mtSbdMessage.transmitLimit     >= 0  &&  mtSbdMessage.transmitLimit    <= 5)  &&
              (mtSbdMessage.batteryCutoff     >= 0  &&  mtSbdMessage.batteryCutoff    <= 12)  &&
              (mtSbdMessage.resetFlag         == 0  ||  mtSbdMessage.resetFlag        == 255))
          {
            DEBUG_PRINTLN("Info - All received values within accepted ranges.");

            sampleInterval    = mtSbdMessage.sampleInterval;    // Update alarm interval
            averageInterval   = mtSbdMessage.averageInterval;   // Update sample average interval
            transmitInterval  = mtSbdMessage.transmitInterval;  // Update transmit interval
            transmitLimit     = mtSbdMessage.transmitLimit;   // Update retransmit limit
            batteryCutoff     = mtSbdMessage.batteryCutoff;     // Update battery cutoff voltage
            resetFlag         = mtSbdMessage.resetFlag;         // Update force reset flag
          }
          else
          {
            DEBUG_PRINTLN("Warning - Received values exceed accepted range!");
          }
        }
        else
        {
          DEBUG_PRINTLN("Warning - MT-SBD message incorrect size!");
        }
      }
      else
      {
        DEBUG_PRINT("Warning - Transmission failed with error code "); DEBUG_PRINTLN(returnCode);
        blinkLed(PIN_LED_RED, 10, 500);
      }
    }
    else
    {
      DEBUG_PRINT("Warning - Transmission failed with error code ");
      DEBUG_PRINTLN(returnCode);
      blinkLed(PIN_LED_RED, 10, 500);
    }
  }

  petDog();

  // Store return status code
  transmitStatus = returnCode;
  DEBUG_PRINT("transmitStatus: "); DEBUG_PRINTLN(transmitStatus);
  moSbdMessage.transmitStatus = transmitStatus;

  // Store message in transmit buffer if transmission or modem begin fails
  if (returnCode != ISBD_SUCCESS)
  {
    failureCounter++;
  }

  // Clear transmit buffer if program running for the first time //TODO Why is this here?
  if (firstTimeFlag)
  {
    memset(moSbdBuffer, 0x00, sizeof(moSbdBuffer)); // Clear moSbdBuffer array
  }

  // Put modem to sleep
  if (returnCode != ISBD_NO_MODEM_DETECTED) {
    DEBUG_PRINTLN("Info - Putting modem to sleep...");
    returnCode = modem.sleep();
    if (returnCode != ISBD_SUCCESS)
    {
      DEBUG_PRINT("Warning - Sleep failed error "); DEBUG_PRINTLN(returnCode);
    }
  }

  // Close the Iridium serial port
  IRIDIUM_PORT.end();

  // Disable power to the RockBLOCK 9603
  disable5V();

  // Reset transmit counter
  transmitCounter = 0;

  // Stop the loop timer
  timer.iridium = millis() - loopStartTime;

  // Write duration of last transmission to union
  moSbdMessage.transmitDuration = timer.iridium / 1000;

  // Check if reset flag was transmitted
  if (resetFlag)
  {
    DEBUG_PRINTLN("Info - Forced system reset...");
    digitalWrite(PIN_LED_RED, HIGH); // Turn on LED
    forceReset();
  }
}

// Non-blocking RockBLOCK callback function can be called during transmit or GNSS signal acquisition
bool ISBDCallback()
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis > 1000)
  {
    previousMillis = currentMillis;
    petDog(); // Reset the Watchdog Timer
    digitalWrite(PIN_LED_GREEN, !digitalRead(PIN_LED_GREEN)); // Blink LED
  }
  return true;
}

#if DEBUG_IRIDIUM
// Callback to sniff the conversation with the Iridium modem
void ISBDConsoleCallback(IridiumSBD *device, char c)
{
  DEBUG_WRITE(c);
}

// Callback to to monitor Iridium modem library's run state
void ISBDDiagsCallback(IridiumSBD *device, char c)
{
  DEBUG_WRITE(c);
}
#endif
