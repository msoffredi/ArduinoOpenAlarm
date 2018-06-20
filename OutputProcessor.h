#ifndef OUTPUTPROCESSOR_H
#define OUTPUTPROCESSOR_H

#if defined(ARDUINO)
 #if ARDUINO >= 100
  #include <Arduino.h>
 #else
  #include <wiring.h>
 #endif 
#endif

#include "AlarmOutput.h"
#include "AlarmConfig.h"
#include "Alarm.h"
#include "Language.h"

// Beeper related constants
#define BEEPER_PIN 7
#define BEEP_DURATION 30
#define BEEP_REPETITION_DURATION 100
#define BEEP_COMMAND_ERROR_DURATION 500
#define BEEP_COMMAND_ACCEPTED_REPETITIONS 3

class OutputProcessor
{
private:
public:
    virtual void processOutput(AlarmOutput outputObj) = 0;
    virtual void processAlarmStatus(String statuses) = 0;
    virtual void processBell(bool bellStatus) = 0;
    
    #ifdef ALARM_BEEPER_AVAILABLE
    static void beep(uint8_t repetition = 1, uint16_t repetitionDuration = BEEP_REPETITION_DURATION, uint16_t duration = BEEP_DURATION);
    #endif
    
};

#endif /* OUTPUTPROCESSOR_H */

