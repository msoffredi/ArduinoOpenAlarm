#ifndef DISARMEDMODE_H
#define DISARMEDMODE_H

#if defined(ARDUINO)
 #if ARDUINO >= 100
  #include <Arduino.h>
 #else
  #include <wiring.h>
 #endif 
#endif

#include "AlarmConfig.h"
#include "WirelessRF.h"
#include "Alarm.h"
#include "CommandPreprocessor.h"
#include "OutputProcessor.h"
#include "Language.h"

class DisarmedMode
{
private:
    Alarm* alarm;
    CommandPreprocessor* commandPreprocessor;
    OutputProcessor* outProcessor;
    uint16_t userCode;
    uint16_t adminCode;
            
    void processCommand(AlarmCommand command);
    void listSensors();
    void learnNewWirelessDevice();
    void learnNewTwoStatesWirelessDevice();
    uint8_t sensorExistsInAlarm(String sensorID);
    void processAlarmStatus();
    void addSensor(AlarmCommand* commandObj);
    void delSensor(AlarmCommand* commandObj);
    void arm(AlarmCommand* commandObj);
    void enterAdminMode(AlarmCommand* commandObj);
    
public:
    DisarmedMode(Alarm* alarm, CommandPreprocessor* commPP, OutputProcessor* outP);
    void loop();
    
};

#endif /* DISARMEDMODE_H */

