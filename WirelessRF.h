#ifndef WIRELESSRF_H
#define WIRELESSRF_H

#if defined(ARDUINO)
 #if ARDUINO >= 100
  #include <Arduino.h>
 #else
  #include <wiring.h>
 #endif 
#endif
 
#include <RCSwitch.h>

// Timeout in milliseconds for when we have to wait for communication to happen
#define WAIT_RF_TIMEOUT 20000

// Pin where the RF receiver will be connected to and has to be an interrupt 
// enabled pin.
#define RF_RECEIVE_PIN 2

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
