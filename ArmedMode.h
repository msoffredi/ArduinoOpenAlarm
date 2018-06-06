#ifndef ARMEDMODE_H
#define ARMEDMODE_H

#if defined(ARDUINO)
 #if ARDUINO >= 100
  #include <Arduino.h>
 #else
  #include <wiring.h>
 #endif 
#endif

#include "AlarmConfig.h"
#include "CommandPreprocessor.h"
#include "Alarm.h"
#include "OutputProcessor.h"
#include "Language.h"
#include "EEPROMHandler.h"

class ArmedMode
{
private:
    Alarm* alarm;
    CommandPreprocessor* commandPreprocessor;
    OutputProcessor* outProcessor;
    uint16_t userCode;
    bool bellTriggered;
    EEPROMHandler* eeprom;

    void processCommand(AlarmCommand command);
    
protected:
    void disarm(AlarmCommand* commandObj);
    void setBellOff();
    void ringBell();
    
public:
    ArmedMode(Alarm* alarm, CommandPreprocessor* commPP, OutputProcessor* outP, EEPROMHandler* eeprom);
    void loop();
    
};

#endif /* ARMEDMODE_H */

