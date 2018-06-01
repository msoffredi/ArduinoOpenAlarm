#include "EEPROMHandler.h"

EEPROMHandler::EEPROMHandler()
{
    this->message = MESSAGE_NONE;
            
    String eepromVersion = this->readVersion();
    char softwareVersion[EEPROM_VERSION_LEN] = SOFTWARE_VERSION;
    
    if (eepromVersion != SOFTWARE_VERSION)
    {
        this->clearEEPROM();
        EEPROM.put(EEPROM_VERSION_ADDR, softwareVersion);
        this->firstTime = true;
    }
    else
    {
        this->firstTime = false;
    }
}

void EEPROMHandler::clearEEPROM()
{
    for (int x=0; x<EEPROM.length(); x++) 
    {
        EEPROM.update(x, 0);
    }
}

String EEPROMHandler::readVersion()
{
    char version[EEPROM_VERSION_LEN] = "";
    EEPROM.get(EEPROM_VERSION_ADDR, version);
    
    return String(version);
}

bool EEPROMHandler::isFirstTime()
{
    return this->firstTime;
}

void EEPROMHandler::setMessage(uint8_t message)
{
    this->message = message;
}

uint8_t EEPROMHandler::getMessage()
{
    return this->message;
}