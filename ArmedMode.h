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

class ArmedMode
{
private:
    Alarm* alarm;
    CommandPreprocessor* commandPreprocessor;
    OutputProcessor* outProcessor;
    uint16_t userCode;
    bool bellTriggered;

    void processCommand(AlarmCommand command);
    void disarm(AlarmCommand* commandObj);
    
public:
    ArmedMode(Alarm* alarm, CommandPreprocessor* commPP, OutputProcessor* outP);
    void loop();
    
};

#endif /* ARMEDMODE_H */

