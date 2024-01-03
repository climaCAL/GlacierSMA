// Calculate statistics
void calculateStats()
{
  // Write data to union
  moSbdMessage.temperatureInt = temperatureIntStats.average()   * 100;          // Mean internal temperature (°C)
  moSbdMessage.humidityInt    = humidityIntStats.average()      * 100;          // Mean internal humidity (%)
  moSbdMessage.pressureExt    = (pressureExtStats.average()     - 400) * 100;   // Mean external pressure (hPa)
  moSbdMessage.temperatureExt = temperatureExtStats.average()   * 100;          // Mean external temperature (°C)
  moSbdMessage.humidityExt    = humidityExtStats.average()      * 100;          // Mean external humidity (%)
  moSbdMessage.solar          = solarStats.average()            * 10000;        // Mean solar irradiance (lx)
  moSbdMessage.voltage        = batteryStats.average()          * 100;          // Mean battery voltage (V)

  // Calculate mean wind speed and direction vectors
  windVectors();

  // Clear all statistics objects
  clearStats();

  // Clear wind gust speed and direction maximums
  windGustSpeed = 0;
  windGustDirection = 0;
  windDirectionSector = 0;
}

// Clear statistics objects
void clearStats()
{
  batteryStats.clear();
  temperatureIntStats.clear();
  humidityIntStats.clear();
  pressureExtStats.clear();
  temperatureExtStats.clear();
  humidityExtStats.clear();
  solarStats.clear();
  windSpeedStats.clear();
  uStats.clear();
  vStats.clear();
}

// Print statistics
void printStats()
{
  printLine();
  DEBUG_PRINTLN(F("Statistics"));
  printLine();
  DEBUG_PRINT("Datetime: ");      printTab(1);  printDateTime();
  DEBUG_PRINT(F("Voltage"));      printTab(2);
  DEBUG_PRINT(F("Samples: "));    DEBUG_PRINT(batteryStats.count());            printTab(1);
  DEBUG_PRINT(F("Min: "));        DEBUG_PRINT(batteryStats.minimum());          printTab(1);
  DEBUG_PRINT(F("Max: "));        DEBUG_PRINT(batteryStats.maximum());          printTab(1);
  DEBUG_PRINT(F("Mean: "));       DEBUG_PRINTLN(batteryStats.average());
  DEBUG_PRINT(F("Temp Int"));                                                   printTab(1);
  DEBUG_PRINT(F("Samples: "));    DEBUG_PRINT(temperatureIntStats.count());     printTab(1);
  DEBUG_PRINT(F("Min: "));        DEBUG_PRINT(temperatureIntStats.minimum());   printTab(1);
  DEBUG_PRINT(F("Max: "));        DEBUG_PRINT(temperatureIntStats.maximum());   printTab(1);
  DEBUG_PRINT(F("Mean: "));       DEBUG_PRINTLN(temperatureIntStats.average());
  DEBUG_PRINT(F("Humidity Int"));                                               printTab(1);
  DEBUG_PRINT(F("Samples: "));    DEBUG_PRINT(humidityIntStats.count());        printTab(1);
  DEBUG_PRINT(F("Min: "));        DEBUG_PRINT(humidityIntStats.minimum());      printTab(1);
  DEBUG_PRINT(F("Max: "));        DEBUG_PRINT(humidityIntStats.maximum());      printTab(1);
  DEBUG_PRINT(F("Mean: "));       DEBUG_PRINTLN(humidityIntStats.average());
  DEBUG_PRINT(F("Pressure Ext"));                                               printTab(1);
  DEBUG_PRINT(F("Samples: "));    DEBUG_PRINT(pressureExtStats.count());        printTab(1);
  DEBUG_PRINT(F("Min: "));        DEBUG_PRINT(pressureExtStats.minimum());      printTab(1);
  DEBUG_PRINT(F("Max: "));        DEBUG_PRINT(pressureExtStats.maximum());      printTab(1);
  DEBUG_PRINT(F("Mean: "));       DEBUG_PRINTLN(pressureExtStats.average());
  DEBUG_PRINT(F("Temp Ext"));                                                   printTab(1);
  DEBUG_PRINT(F("Samples: "));    DEBUG_PRINT(temperatureExtStats.count());     printTab(1);
  DEBUG_PRINT(F("Min: "));        DEBUG_PRINT(temperatureExtStats.minimum());   printTab(1);
  DEBUG_PRINT(F("Max: "));        DEBUG_PRINT(temperatureExtStats.maximum());   printTab(1);
  DEBUG_PRINT(F("Mean: "));       DEBUG_PRINTLN(temperatureExtStats.average());
  DEBUG_PRINT(F("Humidity Ext"));                                               printTab(1);
  DEBUG_PRINT(F("Samples: "));    DEBUG_PRINT(humidityExtStats.count());        printTab(1);
  DEBUG_PRINT(F("Min: "));        DEBUG_PRINT(humidityExtStats.minimum());      printTab(1);
  DEBUG_PRINT(F("Max: "));        DEBUG_PRINT(humidityExtStats.maximum());      printTab(1);
  DEBUG_PRINT(F("Mean: "));       DEBUG_PRINTLN(humidityExtStats.average());
  DEBUG_PRINT(F("Solar"));                                                      printTab(2);
  DEBUG_PRINT(F("Samples: "));    DEBUG_PRINT(solarStats.count());              printTab(1);
  DEBUG_PRINT(F("Min: "));        DEBUG_PRINT(solarStats.minimum());            printTab(1);
  DEBUG_PRINT(F("Max: "));        DEBUG_PRINT(solarStats.maximum());            printTab(1);
  DEBUG_PRINT(F("Mean: "));       DEBUG_PRINTLN(solarStats.average());
  DEBUG_PRINT(F("Wind speed"));   printTab(1);
  DEBUG_PRINT(F("Samples: "));    DEBUG_PRINT(windSpeedStats.count());          printTab(1);
  DEBUG_PRINT(F("Min: "));        DEBUG_PRINT(windSpeedStats.minimum());        printTab(1);
  DEBUG_PRINT(F("Max: "));        DEBUG_PRINT(windSpeedStats.maximum());        printTab(1);
  DEBUG_PRINT(F("Mean: "));       DEBUG_PRINTLN(windSpeedStats.average());
  DEBUG_PRINT(F("vn"));                                                         printTab(2);
  DEBUG_PRINT(F("Samples: "));    DEBUG_PRINT(vStats.count());                  printTab(1);
  DEBUG_PRINT(F("Min: "));        DEBUG_PRINT(vStats.minimum());                printTab(1);
  DEBUG_PRINT(F("Max: "));        DEBUG_PRINT(vStats.maximum());                printTab(1);
  DEBUG_PRINT(F("Mean: "));       DEBUG_PRINTLN(vStats.average());
  DEBUG_PRINT(F("ve"));                                                         printTab(2);
  DEBUG_PRINT(F("Samples: "));    DEBUG_PRINT(uStats.count());                  printTab(1);
  DEBUG_PRINT(F("Min: "));        DEBUG_PRINT(uStats.minimum());                printTab(1);
  DEBUG_PRINT(F("Max: "));        DEBUG_PRINT(uStats.maximum());                printTab(1);
  DEBUG_PRINT(F("Mean: "));       DEBUG_PRINTLN(uStats.average());
  DEBUG_PRINT(F("Wind gust speed: "));      printTab(1);  DEBUG_PRINTLN(windGustSpeed);
  DEBUG_PRINT(F("Wind gust direction: "));  printTab(1);  DEBUG_PRINTLN(windGustDirection);
}
