#ifndef EEPROMHANDLER_H
#define EEPROMHANDLER_H

#if defined(ARDUINO)
 #if ARDUINO >= 100
  #include <Arduino.h>
 #else
  #include <wiring.h>
 #endif 
#endif
 
#define EEPROM_VERSION_ADDR 0
#define EEPROM_VERSION_LEN 10

#define EEPROM_NUMSENSORS_ADDR 10
#define EEPROM_USER_CODE 11
#define EEPROM_ADMIN_CODE 13
// 15-39 = 24 free bytes with fixed address available
#define EEPROM_SENSORS_ADDR 40

#include "EEPROM.h"
#include "AlarmConfig.h"

class EEPROMHandler
{
private:
    bool firstTime;
    
    void clearEEPROM();
    String readVersion();
    
public:
    EEPROMHandler();
    bool isFirstTime();
        
};

#endif /* EEPROMHANDLER_H */

