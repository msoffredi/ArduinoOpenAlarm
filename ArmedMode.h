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
#include "AlarmCommon.h"

class ArmedMode
{
private:
    CommonAlarmSharedObjects *common;
    uint16_t userCode;
    bool bellTriggered;

    void processCommand(AlarmCommand command);
    
protected:
    void disarm(AlarmCommand* commandObj);
    void ringBell();
    
public:
    ArmedMode(CommonAlarmSharedObjects* common);
    void loop();
    
};

#endif /* ARMEDMODE_H */

