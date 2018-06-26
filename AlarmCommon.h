#ifndef ALARMCOMMON_H
#define ALARMCOMMON_H

#include "CommandPreprocessor.h"
#include "Alarm.h"
#include "OutputProcessor.h"
#include "EEPROMHandler.h"

class CommonAlarmSharedObjects 
{
public:
    Alarm *alarm;
    CommandPreprocessor *commPP;
    OutputProcessor *outP;
    EEPROMHandler *eeprom;
    
    CommonAlarmSharedObjects(Alarm* alarm, CommandPreprocessor* commPP, OutputProcessor* outP, EEPROMHandler* eeprom);
};


#endif /* ALARMCOMMON_H */

