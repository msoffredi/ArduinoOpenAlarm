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
        else if (command == F(USB_ALARM_COMMAND_DISARM))
        {
            commandObj.setCommand(ALARM_COMMAND_DISARM);
            this->extractParameters(serialInput, &commandObj);
        }
        else if (command == F(USB_ALARM_COMMAND_ENTER_ADMIN_MODE))
        {
            commandObj.setCommand(ALARM_COMMAND_ENTER_ADMIN_MODE);
            this->extractParameters(serialInput, &commandObj);
        }
        else if (command == F(USB_ALARM_COMMAND_EXIT_ADMIN_MODE))
        {
            commandObj.setCommand(ALARM_COMMAND_EXIT_ADMIN_MODE);
            this->extractParameters(serialInput, &commandObj);
        }
        else if (command == F(USB_ALARM_COMMAND_DEL_SENSOR))
        {
            commandObj.setCommand(ALARM_COMMAND_DEL_SENSOR);
            this->extractParameters(serialInput, &commandObj);
        }
        else if (command == F(USB_ALARM_COMMAND_CHANGE_USER_CODE))
        {
            commandObj.setCommand(ALARM_COMMAND_CHANGE_USER_CODE);
            this->extractParameters(serialInput, &commandObj);
        }
        else if (command == F(USB_ALARM_COMMAND_CHANGE_ADMIN_CODE))
        {
            commandObj.setCommand(ALARM_COMMAND_CHANGE_ADMIN_CODE);
            this->extractParameters(serialInput, &commandObj);
        }
        else if (command == F(USB_ALARM_COMMAND_SENSOR_OFF))
        {
            commandObj.setCommand(ALARM_COMMAND_SENSOR_OFF);
            this->extractParameters(serialInput, &commandObj);
        }
        else if (command == F(USB_ALARM_COMMAND_SENSOR_ON))
        {
            commandObj.setCommand(ALARM_COMMAND_SENSOR_ON);
            this->extractParameters(serialInput, &commandObj);
        }
        else if (command == F(USB_ALARM_COMMAND_SENSOR_DELAYED))
        {
            commandObj.setCommand(ALARM_COMMAND_SENSOR_DELAYED);
            this->extractParameters(serialInput, &commandObj);
        }
        else if (this->stringIsNumeric(command))
        {
            commandObj.setCommand(ALARM_COMMAND_NUMERIC_CODE);
            commandObj.setParameter(1, command);
        }
    }
    
    this->lastCommand = commandObj;
    
    return commandObj;
}

bool USBCommandPreprocessor::stringIsNumeric(String var)
{
    bool returnValue = true;
    
    for (int x=0; x<var.length(); x++)
    {
        if (var[x] < '0' || var[x] > '9')
        {
            returnValue = false;
            break;
        }
    }
    
    return returnValue;
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
