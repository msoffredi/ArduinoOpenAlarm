#ifndef USBCOMMANDPREPROCESSOR_H
#define USBCOMMANDPREPROCESSOR_H

#if defined(ARDUINO)
 #if ARDUINO >= 100
  #include <Arduino.h>
 #else
  #include <wiring.h>
 #endif 
#endif
 
#include "AlarmCommand.h"
#include "CommandPreprocessor.h"

// Software related commands
#define USB_ALARM_COMMAND_VERSION "ver"

// Alarm related commands
#define USB_ALARM_COMMAND_LIST_SENSORS "listsensors"
#define USB_ALARM_COMMAND_STATUS "status"
#define USB_ALARM_COMMAND_ARM "arm"
#define USB_ALARM_COMMAND_ENTER_ADMIN_MODE "admin"
#define USB_ALARM_COMMAND_EXIT_ADMIN_MODE "exitadmin"

// Format is: adds <pin>
#define USB_ALARM_COMMAND_ADD_SENSOR "adds"

// Wireless related commands
#define USB_ALARM_COMMAND_WIRELESS_LEARN "wlearn"
#define USB_ALARM_COMMAND_WIRELESS_LEARN_2S "wlearn2"

class USBCommandPreprocessor : public CommandPreprocessor
{
private:
    String getCommandFromString(String usbString);
    void extractParameters(String serialInput, AlarmCommand* commandObj);
    
public:
    AlarmCommand getNextCommand();
    AlarmCommand getLastCommand();
    
};

#endif /* USBCOMMANDPREPROCESSOR_H */

