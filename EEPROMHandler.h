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

#define MESSAGE_NONE 0
#define MESSAGE_READ_USER_CODE 1

#include "EEPROM.h"
#include "AlarmConfig.h"

class EEPROMHandler
{
private:
    bool firstTime;
    uint8_t message;
    
    void clearEEPROM();
    String readVersion();
    
public:
    EEPROMHandler();
    bool isFirstTime();
    void setMessage(uint8_t message);
    uint8_t getMessage();
        
};

#endif /* EEPROMHANDLER_H */

