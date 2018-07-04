/*
 * This Alternative Command Processor allows you to integrate standard keypads
 * to your ArduinoOpenAlarm. This version is for the direct connect version and
 * not for the I2C versions available.
 * 
 * This command processor requires an external library you have to install on
 * your system unless you already have it. You can find the library here:
 * https://playground.arduino.cc/uploads/Code/keypad.zip
 * 
 * And we strongly recommend you to read the library page and test your keypad
 * before jumping into the ArduinoOpenAlarm integration. The page can be found 
 * here: https://playground.arduino.cc/Code/Keypad
 * 
 * For an easy integration please follow the next steps:
 * 
 * 1) Add the following line to the top of your ArduinoOpenAlarm.ino file:
 * 
 * #include <Keypad.h>
 * 
 * 2) Copy the following files to the project root directory:
 *
 * /input/MatrixKeypadCommandPreprocessor.h
 * /input/MatrixKeypadCommandPreprocessor.cpp
 * 
 * 3) Replace the following lines of your ArduinoOpenAlarm.ino file:
 * 
 * #include "USBCommandPreprocessor.h"
 * USBCommandPreprocessor commPP;
 * 
 * with the following ones:
 * 
 * #include "MatrixKeypadCommandPreprocessor.h"
 * MatrixKeypadCommandPreprocessor commPP;
 * 
 * 4) Edit the keypad configuration information below to match your keypad
 * including the rows and columns definition like:
 * 
 * #define KEYPAD_ROWS 4
 * #define KEYPAD_COLS 4
 *
 * But also the keys map and the pins your keypad is connected to. 
 * 
 * Note: Commands with parameters must be entered in the format: 
 * <command>*<parameter1>[*<parameterN>]#
 * 
 * For example: A*9999# 
 * Will try to enter into Admin mode using admin code 9999
 */

#ifndef MATRIXKEYPADCOMMANDPREPROCESSOR_H
#define MATRIXKEYPADCOMMANDPREPROCESSOR_H

#if defined(ARDUINO)
 #if ARDUINO >= 100
  #include <Arduino.h>
 #else
  #include <wiring.h>
 #endif 
#endif
 
#include "CommandPreprocessor.h"
#include "AlarmConfig.h"
#include "OutputProcessor.h"
#include "Keypad.h"

// Software related commands
#define USB_ALARM_COMMAND_VERSION "A99"

// Alarm related commands
#define USB_ALARM_COMMAND_LIST_SENSORS "A1"
#define USB_ALARM_COMMAND_LIST_SENSORS "A11"
#define USB_ALARM_COMMAND_STATUS "B1"
#define USB_ALARM_COMMAND_ENTER_ADMIN_MODE "A"
#define USB_ALARM_COMMAND_EXIT_ADMIN_MODE "D"
#define USB_ALARM_COMMAND_NUMBER_SENSORS "A12"

// Syntax: C99*<admin_code>*1#
#define USB_ALARM_COMMAND_FACTORY_RESET "C99"

// Syntax: A2*<pin>#
#define USB_ALARM_COMMAND_ADD_SENSOR "A2"

// Syntax: A3*<sensorID>#
// sensorID can be obtained by listing sensors with lists
#define USB_ALARM_COMMAND_DEL_SENSOR "A3"

#define USB_ALARM_COMMAND_SENSOR_OFF "A4"
#define USB_ALARM_COMMAND_SENSOR_ON "A5"
#define USB_ALARM_COMMAND_SENSOR_ON "A10"

#define USB_ALARM_COMMAND_CHANGE_USER_CODE "A6"
#define USB_ALARM_COMMAND_CHANGE_ADMIN_CODE "A7"

// Wireless related commands
#define USB_ALARM_COMMAND_WIRELESS_LEARN "A8"
#define USB_ALARM_COMMAND_WIRELESS_LEARN_2S "A9"

// Keypad number of rows and columns
#define KEYPAD_ROWS 4
#define KEYPAD_COLS 4

class MatrixKeypadCommandPreprocessor : public CommandPreprocessor
{
private:
    String nextCommand;

    char keys[KEYPAD_ROWS][KEYPAD_COLS] = {
      {'1','2','3','A'},
      {'4','5','6','B'},
      {'7','8','9','C'},
      {'*','0','#','D'}
    };

    // Pins connected to the keypad
    byte rowPins[KEYPAD_ROWS] = {30, 32, 34, 36};
    byte colPins[KEYPAD_COLS] = {38, 40, 42, 44};
    
    Keypad keypad = Keypad(makeKeymap(this->keys), this->rowPins, this->colPins, KEYPAD_ROWS, KEYPAD_COLS);
    
    String getCommandFromString(String usbString);
    void extractParameters(String serialInput, AlarmCommand* commandObj);
    bool stringIsNumeric(String var);
    
public:
    MatrixKeypadCommandPreprocessor();
    AlarmCommand getNextCommand();
    AlarmCommand getLastCommand();
    
};

#endif /* MATRIXKEYPADCOMMANDPREPROCESSOR_H */

