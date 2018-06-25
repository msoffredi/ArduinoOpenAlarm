#ifndef WIRELESSRF_H
#define WIRELESSRF_H

#if defined(ARDUINO)
 #if ARDUINO >= 100
  #include <Arduino.h>
 #else
  #include <wiring.h>
 #endif 
#endif

#include "AlarmConfig.h"
#include <RCSwitch.h>

class WirelessRF
{
private:
    RCSwitch switchObj = RCSwitch();
    
public:
    WirelessRF();
    String getNewRFDeviceRead();
    String getRFDeviceRead();
    
};

#endif /* WIRELESSRF_H */
