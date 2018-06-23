#ifndef USBCOMMANDPREPROCESSOR_H
#define USBCOMMANDPREPROCESSOR_H

#if defined(ARDUINO)
 #if ARDUINO >= 100
  #include <Arduino.h>
 #else
  #include <wiring.h>
 #endif 
#endif
 
#include "CommandPreprocessor.h"

// Software related commands
#define USB_ALARM_COMMAND_VERSION "ver"

// Alarm related commands
#define USB_ALARM_COMMAND_LIST_SENSORS "lists"
#define USB_ALARM_COMMAND_STATUS "status"
#define USB_ALARM_COMMAND_ARM "arm"
#define USB_ALARM_COMMAND_DISARM "disarm"
#define USB_ALARM_COMMAND_ENTER_ADMIN_MODE "admin"
#define USB_ALARM_COMMAND_EXIT_ADMIN_MODE "exit"

// Syntax: adds <pin>
#define USB_ALARM_COMMAND_ADD_SENSOR "adds"

// Syntax: dels <sensorID>
// sensorID can be obtained by listing sensors with lists
#define USB_ALARM_COMMAND_DEL_SENSOR "dels"

#define USB_ALARM_COMMAND_SENSOR_OFF "soff"
#define USB_ALARM_COMMAND_SENSOR_ON "son"
#define USB_ALARM_COMMAND_SENSOR_DELAYED "sd"

#define USB_ALARM_COMMAND_CHANGE_USER_CODE "ucode"
#define USB_ALARM_COMMAND_CHANGE_ADMIN_CODE "acode"

// Wireless related commands
#define USB_ALARM_COMMAND_WIRELESS_LEARN "wlearn"
#define USB_ALARM_COMMAND_WIRELESS_LEARN_2S "wlearn2"

class USBCommandPreprocessor : public CommandPreprocessor
{
private:
    String getCommandFromString(String usbString);
    void extractParameters(String serialInput, AlarmCommand* commandObj);
    bool stringIsNumeric(String var);
    
public:
    AlarmCommand getNextCommand();
    AlarmCommand getLastCommand();
    
};

#endif /* USBCOMMANDPREPROCESSOR_H */

