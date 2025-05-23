void printLine()
{
  for (byte i = 0; i < 80; i++)
  {
    DEBUG_PRINT("-");
  }
  DEBUG_PRINTLN();
}

void printTab(byte _times)
{
  for (byte i = 0; i < _times; i++)
  {
    DEBUG_PRINT("\t");
  }
}

// Print user-defined beacon settings
void printWakeUp(unsigned int sampleNumber)
{
  DEBUG_PRINTLN();
  printLine();
  DEBUG_PRINT("Station awake, collecting sample #"); DEBUG_PRINTLN(sampleNumber);
  printLine();
}

// Print user-defined beacon settings
void printSettings()
{
  printLine();
  DEBUG_PRINTLN("Current Settings");
  printLine();
  DEBUG_PRINT("sampleInterval: ");    printTab(1);  DEBUG_PRINTLN(sampleInterval);
  DEBUG_PRINT("averageInterval: ");   printTab(1);  DEBUG_PRINTLN(averageInterval);
  DEBUG_PRINT("transmitInterval: ");  printTab(1);  DEBUG_PRINTLN(transmitInterval);
  DEBUG_PRINT("transmitLimit: ");     printTab(2);  DEBUG_PRINTLN(transmitLimit);
  DEBUG_PRINT("transmitBuffer: ");    printTab(1);  DEBUG_PRINTLN(transmitBuffer);
  DEBUG_PRINT("gnssTimeout: ");       printTab(2);  DEBUG_PRINTLN(gnssTimeout);
  DEBUG_PRINT("iridiumTimeout: ");    printTab(1);  DEBUG_PRINTLN(iridiumTimeout);
  DEBUG_PRINT("loggingMode: ");       printTab(2);  DEBUG_PRINTLN(loggingMode);
  DEBUG_PRINT("batteryCutoff: ");     printTab(2);  DEBUG_PRINTLN(batteryCutoff);
  DEBUG_PRINT("resetFlag: ");         printTab(2);  DEBUG_PRINTLN(resetFlag);
  DEBUG_PRINT("freeRam(): ");         printTab(2);  DEBUG_PRINTLN(freeRam()); // Does not really belong here but is convenient...
  printLine();
}

void printTimers()
{
  printLine();
  DEBUG_PRINTLN("Function Execution Timers");
  printLine();
  DEBUG_PRINT("readRtc: ");         printTab(1);  DEBUG_PRINTLN(timer.readRtc);
  DEBUG_PRINT("readBattery: ");     printTab(1);  DEBUG_PRINTLN(timer.readBattery);
  DEBUG_PRINT("readBme280Ext: ");   printTab(1);  DEBUG_PRINTLN(timer.readBme280Ext);
  DEBUG_PRINT("readBme280Int: ");   printTab(1);  DEBUG_PRINTLN(timer.readBme280Int);
  DEBUG_PRINT("readLsm303: ");      printTab(1);  DEBUG_PRINTLN(timer.readLsm303);
  DEBUG_PRINT("readVeml7700: ");    printTab(1);  DEBUG_PRINTLN(timer.readVeml7700);
  //DEBUG_PRINT("readHmp60: ");       printTab(1);  DEBUG_PRINTLN(timer.readHmp60);
  //DEBUG_PRINT("readSht31: ");       printTab(1);  DEBUG_PRINTLN(timer.readSht31);
  //DEBUG_PRINT("read5103L: ");       printTab(1);  DEBUG_PRINTLN(timer.read5103L);
  //DEBUG_PRINT("read7911: ");        printTab(1);  DEBUG_PRINTLN(timer.read7911);
  DEBUG_PRINT("readBridge: ");       printTab(1);  DEBUG_PRINTLN(timer.readBridge);
  DEBUG_PRINT("readGnss: ");        printTab(1);  DEBUG_PRINTLN(timer.readGnss);
  DEBUG_PRINT("writeMicroSd: ");    printTab(1);  DEBUG_PRINTLN(timer.writeMicroSd);
  DEBUG_PRINT("transmitData: ");    printTab(1);  DEBUG_PRINTLN(timer.iridium);
  DEBUG_PRINT("freeRam(): ");       printTab(1);  DEBUG_PRINTLN(freeRam()); // Does not really belong here but is convenient...
  printLine();
}

// Print contents of union/structure storing Mobile Originated (MO) SBD message data
void printMoSbd()
{
  printLine();
  DEBUG_PRINTLN("MO-SBD Message Data");
  printLine();

  DEBUG_PRINT("unixtime:");         printTab(2);  DEBUG_PRINTLN(moSbdMessage.unixtime);
  DEBUG_PRINT("temperatureInt:");   printTab(2);  DEBUG_PRINTLN(moSbdMessage.temperatureInt);
  DEBUG_PRINT("humidityInt:");      printTab(2);  DEBUG_PRINTLN(moSbdMessage.humidityInt);
  DEBUG_PRINT("pressureExt:");      printTab(2);  DEBUG_PRINTLN(moSbdMessage.pressureExt);
  DEBUG_PRINT("temperatureExt:");   printTab(2);  DEBUG_PRINTLN(moSbdMessage.temperatureExt);
  DEBUG_PRINT("humidityExt:");      printTab(2);  DEBUG_PRINTLN(moSbdMessage.humidityExt);
  DEBUG_PRINT("solar:");            printTab(3);  DEBUG_PRINTLN(moSbdMessage.solar);
  DEBUG_PRINT("pitch:");            printTab(3);  DEBUG_PRINTLN(moSbdMessage.pitch);
  DEBUG_PRINT("roll:");             printTab(3);  DEBUG_PRINTLN(moSbdMessage.roll);
  DEBUG_PRINT("windSpeed:");        printTab(2);  DEBUG_PRINTLN(moSbdMessage.windSpeed);
  DEBUG_PRINT("windDirection:");    printTab(2);  DEBUG_PRINTLN(moSbdMessage.windDirection);
  DEBUG_PRINT("windGustSpeed:");    printTab(2);  DEBUG_PRINTLN(moSbdMessage.windGustSpeed);
  DEBUG_PRINT("windGustDirection:");  printTab(1);  DEBUG_PRINTLN(moSbdMessage.windGustDirection);
  DEBUG_PRINT("latitude:");         printTab(2);  DEBUG_PRINTLN(moSbdMessage.latitude);
  DEBUG_PRINT("longitude:");        printTab(2);  DEBUG_PRINTLN(moSbdMessage.longitude);
  DEBUG_PRINT("satellites:");       printTab(2);  DEBUG_PRINTLN(moSbdMessage.satellites);
  //DEBUG_PRINT("hdop:");             printTab(3);  DEBUG_PRINTLN(moSbdMessage.hdop);
  DEBUG_PRINT("hauteurNeige:");     printTab(2);  DEBUG_PRINTLN(moSbdMessage.hauteurNeige);
  DEBUG_PRINT("voltage:");          printTab(2);  DEBUG_PRINTLN(moSbdMessage.voltage);
  DEBUG_PRINT("transmitDuration:"); printTab(1);  DEBUG_PRINTLN(moSbdMessage.transmitDuration);
  DEBUG_PRINT("transmitStatus:");   printTab(2);  DEBUG_PRINTLN(moSbdMessage.transmitStatus);
  DEBUG_PRINT("iterationCounter:"); printTab(1);  DEBUG_PRINTLN(moSbdMessage.iterationCounter);

  printLine();
}

// Print contents of union/structure storing Mobile Originated (MT) SBD message data
void printMtSbd()
{
  printLine();
  DEBUG_PRINTLN("MT-SBD Message Data");
  printLine();
  DEBUG_PRINT("sampleInterval:");   printTab(2);  DEBUG_PRINTLN(mtSbdMessage.sampleInterval);
  DEBUG_PRINT("averageInterval:");  printTab(1);  DEBUG_PRINTLN(mtSbdMessage.averageInterval);
  DEBUG_PRINT("transmitInterval:"); printTab(1);  DEBUG_PRINTLN(mtSbdMessage.transmitInterval);
  DEBUG_PRINT("transmitLimit:");    printTab(2);  DEBUG_PRINTLN(mtSbdMessage.transmitLimit);
  DEBUG_PRINT("batteryCutoff:");    printTab(2);  DEBUG_PRINTLN(mtSbdMessage.batteryCutoff);
  DEBUG_PRINT("resetFlag:");        printTab(2);  DEBUG_PRINTLN(mtSbdMessage.resetFlag);
  printLine();
}

// Print contents of union/structure
void printMoSbdHex()
{
  DEBUG_PRINTLN("MO-SBD Union/structure ");
  printLine();
  char tempData[16];
  DEBUG_PRINTLN("Byte\tHex");
  for (unsigned i = 0; i < sizeof(moSbdMessage); ++i)
  {
    sprintf(tempData, "%d\t0x%02X", i, moSbdMessage.bytes[i]);
    DEBUG_PRINTLN(tempData);
  }
  printLine();
}

// Print contents of transmit buffer
void printMoSbdBuffer()
{
  printLine();
  DEBUG_PRINTLN("MO-SBD Transmit buffer");
  printLine();
  char tempData[16];
  DEBUG_PRINTLN("Byte\tHex");
  for (unsigned i = 0; i < moSbdBufferSize; ++i)
  {
    sprintf(tempData, "%d\t0x%02X", i, moSbdBuffer[i]);
    DEBUG_PRINTLN(tempData);
  }
}

// Print contents of transmit buffer
void printMtSbdBuffer()
{
  printLine();
  DEBUG_PRINTLN("MT-SBD Transmit buffer");
  printLine();
  // Print contents of mtSbdBuffer in hexadecimal
  char tempData[16];
  DEBUG_PRINTLN("Byte\tHex");
  for (unsigned i = 0; i < mtSbdBufferSize; ++i)
  {
    sprintf(tempData, "%d\t0x%02X", i, mtSbdBuffer[i]);
    DEBUG_PRINTLN(tempData);
  }
}

// Function to print available 32K SRAM memory
extern "C" char *sbrk(int i);
int freeRam()
{
  char stack_dummy = 0;
  return &stack_dummy - sbrk(0);
}
