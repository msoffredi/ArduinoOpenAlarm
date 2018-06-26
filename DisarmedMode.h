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
#include "EEPROMHandler.h"
#include "AlarmCommon.h"

class DisarmedMode
{
private:
    CommonAlarmSharedObjects *common;
    uint16_t userCode;
    uint16_t adminCode;
    uint8_t adminCodeFailures;
    unsigned long adminCodeFailureTime;
            
    void processCommand(AlarmCommand command);
    void listSensors();
    void learnNewWirelessDevice();
    void learnNewTwoStatesWirelessDevice();
    uint8_t sensorExistsInAlarm(String sensorID);
    void processAlarmStatus();
    void addSensor(AlarmCommand* commandObj);
    void delSensor(AlarmCommand* commandObj);
    void enterAdminMode(AlarmCommand* commandObj);
    bool pinNotInBlacklist(uint8_t pin);
    void initUserAndAdminCodes();
    void writeToEEPROM();
    void changeUserCode(AlarmCommand* commandObj);
    void changeAdminCode(AlarmCommand* commandObj);
    void sensorOnOff(AlarmCommand* commandObj, bool power);
    void exitAdmin();
    void setSensorAsDelayed(AlarmCommand* commandObj);
    
protected:
    void arm(AlarmCommand* commandObj);
    
public:
    DisarmedMode(CommonAlarmSharedObjects* common);
    void loop();
    
};

#endif /* DISARMEDMODE_H */

