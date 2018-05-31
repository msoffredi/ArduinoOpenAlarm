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

class OutputProcessor
{
private:
public:
    virtual void processOutput(AlarmOutput outputObj) = 0;
    virtual void processAlarmStatus(String statuses) = 0;
    
};

#endif /* OUTPUTPROCESSOR_H */

