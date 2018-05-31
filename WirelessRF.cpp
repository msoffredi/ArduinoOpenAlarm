#include "WirelessRF.h"

WirelessRF::WirelessRF()
{
    this->switchObj.enableReceive(digitalPinToInterrupt(RF_RECEIVE_PIN));
}

String WirelessRF::getNewRFDeviceRead()
{
    unsigned long start = millis();
    String returnValue = "";
    
    // Clear buffer first
    while (this->switchObj.available())
    {
        if ((millis()-start) >= WAIT_RF_TIMEOUT)
        {
            break;
        }
        
        this->switchObj.resetAvailable();
    }
    
    while ((millis()-start) < WAIT_RF_TIMEOUT && returnValue == "") {
        returnValue = this->getRFDeviceRead();
    }
    
    return returnValue;
}

String WirelessRF::getRFDeviceRead()
{
    String returnValue = "";

    if (this->switchObj.available())
    {
        returnValue = String(this->switchObj.getReceivedValue());
        this->switchObj.resetAvailable();
    }
    
    return returnValue;
}
