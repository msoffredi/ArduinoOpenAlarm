#ifndef ALARM_H
#define ALARM_H

#if defined(ARDUINO)
 #if ARDUINO >= 100
  #include <Arduino.h>
 #else
  #include <wiring.h>
 #endif 
#endif
 
#include "Sensor.h"
#include "WirelessRF.h"

#define MAX_SENSORS 10

#define ALARM_STATUS_DISARMED 0
#define ALARM_STATUS_ARMED 1

#define ALARM_OPERATION_MODE_USER 0
#define ALARM_OPERATION_MODE_ADMIN 1

class Alarm
{
private:
    Sensor sensors[MAX_SENSORS];
    uint8_t numSensors;
    uint8_t status;
    uint8_t operationMode;
    bool bell;
    
    bool checkWiredSensorsActive();
    bool checkWirelessSensorsActive();
    
public:
    Alarm();
    uint8_t addSensor(Sensor sensorPtr);
    void delSensor(uint8_t index);
    uint8_t getStatus();
    void setStatus(uint8_t status);
    uint8_t getNumSensors();
    Sensor* getSensor(uint8_t sensorIdx);
    void loop();
    uint8_t getOperationMode();
    void setOperationMode(uint8_t operationMode);
    void setBell(bool bell);
    bool getBell();
    
};

#endif /* ALARM_H */
