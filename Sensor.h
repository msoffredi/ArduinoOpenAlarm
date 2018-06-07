#ifndef SENSOR_H
#define SENSOR_H

#if defined(ARDUINO)
 #if ARDUINO >= 100
  #include <Arduino.h>
 #else
  #include <wiring.h>
 #endif 
#endif

#include "AlarmConfig.h"

class Sensor 
{
private:
    bool power;
    bool active;
    unsigned long lastActive;
    bool wireless;
    
    // Some wireless magnetic sensors have 2 stages with a code for each of them
    bool twoStates;
    
    // Wired attributes
    uint8_t sensorPin;
    
    // Wireless attributes
    String sensorID;
    // For sensors having 2nd state to get back to inactive (magnetic door wireless sensors for example)
    String sensorInactiveID;
    
public:
    Sensor();
    bool isOn();
    bool isActive();
    void setPower(bool power);
    void setActive(bool activeStatus);
    void clearSensor();
        
    // Wired methods
    void setSensorID(String ID);
    void setSensorPin(uint8_t pin);
    uint8_t getSensorPin();
    
    // Wireless methods
    void setWireless(bool wireless);
    bool isWireless();
    String getSensorID();
    String getTamperID();
    void setSensorInactiveID(String ID);
    String getSensorInactiveID();
    void setTwoStates(bool value);
    bool isTwoStates();
    
};

#endif /* SENSOR_H */
