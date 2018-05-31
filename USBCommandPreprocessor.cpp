#include "USBCommandPreprocessor.h"

AlarmCommand USBCommandPreprocessor::getNextCommand()
{
    String commandParameters[MAX_COMMAND_PARAMETERS], serialInput, command;
    AlarmCommand commandObj;
    
    if (Serial.available()) 
    {
        serialInput = Serial.readStringUntil('\n');
        command = this->getCommandFromString(serialInput);
        
        if (command == F(USB_ALARM_COMMAND_VERSION))
        {
            commandObj.setCommand(ALARM_COMMAND_VERSION);
        }
        else if (command == F(USB_ALARM_COMMAND_WIRELESS_LEARN))
        {
            commandObj.setCommand(ALARM_COMMAND_WIRELESS_LEARN);
        }
        else if (command == F(USB_ALARM_COMMAND_WIRELESS_LEARN_2S))
        {
            commandObj.setCommand(ALARM_COMMAND_WIRELESS_LEARN_2S);
        }
        else if (command == F(USB_ALARM_COMMAND_LIST_SENSORS))
        {
            commandObj.setCommand(ALARM_COMMAND_LIST_SENSORS);
        }
        else if (command == F(USB_ALARM_COMMAND_STATUS))
        {
            commandObj.setCommand(ALARM_COMMAND_ALARM_STATUS);
        }
        else if (command == F(USB_ALARM_COMMAND_ADD_SENSOR))
        {
            commandObj.setCommand(ALARM_COMMAND_ADD_SENSOR);
            this->extractParameters(serialInput, &commandObj);
        }
        else if (command == F(USB_ALARM_COMMAND_ARM))
        {
            commandObj.setCommand(ALARM_COMMAND_ARM);
            this->extractParameters(serialInput, &commandObj);
        }
    }
    
    this->lastCommand = commandObj;
    
    return commandObj;
}

String USBCommandPreprocessor::getCommandFromString(String usbString)
{
    unsigned int indexTo = (usbString.indexOf(' ') >= 0) ? usbString.indexOf(' ') : usbString.length();
    return usbString.substring(0, indexTo);
}

AlarmCommand USBCommandPreprocessor::getLastCommand()
{
    return this->lastCommand;
}

void USBCommandPreprocessor::extractParameters(String serialInput, AlarmCommand* commandObj)
{
    String paramString = serialInput.substring((serialInput.indexOf(' ') >= 0) ? serialInput.indexOf(' ')+1 : serialInput.length());
    unsigned int indexTo, paramIdx = 1;
    
    commandObj->clearParameters();
    
    while (paramString.length() && paramIdx <= MAX_COMMAND_PARAMETERS)
    {
        indexTo = (paramString.indexOf(' ') >= 0) ? paramString.indexOf(' ') : paramString.length();
        commandObj->setParameter(paramIdx++, paramString.substring(0, indexTo));
        
        if (indexTo < paramString.length())
        {
            paramString = paramString.substring(paramString.indexOf(' ')+1);
        }
        else
        {
            paramString = "";
        }
    }
}
