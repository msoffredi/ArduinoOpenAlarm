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
#define ALARM_COMMAND_ENTER_ADMIN_MODE 6
#define ALARM_COMMAND_EXIT_ADMIN_MODE 7
#define ALARM_COMMAND_DEL_SENSOR 8
#define ALARM_COMMAND_DISARM 9
#define ALARM_COMMAND_WIRELESS_LEARN 10
#define ALARM_COMMAND_WIRELESS_LEARN_2S 11
#define ALARM_COMMAND_CHANGE_USER_CODE 12
#define ALARM_COMMAND_CHANGE_ADMIN_CODE 13
#define ALARM_COMMAND_NUMERIC_CODE 14

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

