#ifndef USBOUTPUTPROCESSOR_H
#define USBOUTPUTPROCESSOR_H

#if defined(ARDUINO)
 #if ARDUINO >= 100
  #include <Arduino.h>
 #else
  #include <wiring.h>
 #endif 
#endif

#include "OutputProcessor.h"

class USBOutputProcessor : public OutputProcessor
{
private:
public:
    void processOutput(AlarmOutput outputObj);
    void processAlarmStatus(String statuses);
    
};

#endif /* USBOUTPUTPROCESSOR_H */
