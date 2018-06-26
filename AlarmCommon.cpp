#include "AlarmCommon.h"

CommonAlarmSharedObjects::CommonAlarmSharedObjects(Alarm* alarm, CommandPreprocessor* commPP, OutputProcessor* outP, EEPROMHandler* eeprom)
{
    this->alarm = alarm;
    this->commPP = commPP;
    this->outP = outP;
    this->eeprom = eeprom;
}
