#ifndef ALARMCOMMAND_H
#define ALARMCOMMAND_H

#if defined(ARDUINO)
 #if ARDUINO >= 100
  #include <Arduino.h>
 #else
  #include <wiring.h>
 #endif 
#endif
 
#define ALARM_COMMAND_NONE 0
#define ALARM_COMMAND_VERSION 1
#define ALARM_COMMAND_LIST_SENSORS 2
#define ALARM_COMMAND_ALARM_STATUS 3
#define ALARM_COMMAND_ADD_SENSOR 4
#define ALARM_COMMAND_ARM 5

// Wireless RF commands 10-19
#define ALARM_COMMAND_WIRELESS_LEARN 10
#define ALARM_COMMAND_WIRELESS_LEARN_2S 11

#define MAX_COMMAND_PARAMETERS 10

class AlarmCommand
{
private:
    uint8_t command;
    String parameters[MAX_COMMAND_PARAMETERS];

public:
    AlarmCommand();
    uint8_t getCommand();
    String getParameter(uint8_t);
    void setCommand(uint8_t command);
    void setParameter(uint8_t index, String value);
    void clearParameters();
    
};

#endif /* ALARMCOMMAND_H */

