#ifndef ALARM_H
#define ALARM_H

#if defined(ARDUINO)
 #if ARDUINO >= 100
  #include <Arduino.h>
 #else
  #include <wiring.h>
 #endif 
#endif
 
#include "AlarmConfig.h"
#include "Sensor.h"
#include "EEPROMHandler.h"
#include "WirelessRF.h"

#define ALARM_STATUS_DISARMED 0
#define ALARM_STATUS_ARMED 1

#define ALARM_OPERATION_MODE_USER 0
#define ALARM_OPERATION_MODE_ADMIN 1

#define ALARM_BELL_ON 1
#define ALARM_BELL_OFF 0

class Alarm
{
private:
    Sensor sensors[MAX_SENSORS];
    uint8_t numSensors;
    uint8_t status;
    uint8_t operationMode;
    bool bell;
    EEPROMHandler* eeprom;
    unsigned long armedTime;
    bool delayedArmBeep;
    uint8_t delayedSensorIndex;
    bool delayedSensorActive;
    unsigned long delayedSensorActiveTime;
    
    bool checkWiredSensorsActive();
    bool checkWirelessSensorsActive();
    void initSensors();
    void delayedArmBeeping();
    void delayedSensorBeepingOff();
    
public:
    Alarm(EEPROMHandler* eeprom);
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
    bool noSensorsActive();
    bool isFreePin(uint8_t pin);
    void writeToEEPROM();
    void setDelayedSensor(uint8_t index);
    uint8_t getDelayedSensorIndex();
    
};

#endif /* ALARM_H */
