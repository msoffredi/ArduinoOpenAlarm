#include "MatrixKeypadCommandPreprocessor.h"

MatrixKeypadCommandPreprocessor::MatrixKeypadCommandPreprocessor()
{
    this->nextCommand = "";
}

AlarmCommand MatrixKeypadCommandPreprocessor::getNextCommand()
{
    String commandParameters[MAX_COMMAND_PARAMETERS], command;
    AlarmCommand commandObj;
    char key = this->keypad.getKey();
    
    if (key != NO_KEY)
    {
        #ifdef ALARM_BEEPER_AVAILABLE
        OutputProcessor::beep();
        #endif
        
        if (key == '#')
        {
            this->nextCommand.replace('*', ' ');
            command = this->getCommandFromString(this->nextCommand);

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
                this->extractParameters(this->nextCommand, &commandObj);
            }
            else if (command == F(USB_ALARM_COMMAND_ENTER_ADMIN_MODE))
            {
                commandObj.setCommand(ALARM_COMMAND_ENTER_ADMIN_MODE);
                this->extractParameters(this->nextCommand, &commandObj);
            }
            else if (command == F(USB_ALARM_COMMAND_EXIT_ADMIN_MODE))
            {
                commandObj.setCommand(ALARM_COMMAND_EXIT_ADMIN_MODE);
                this->extractParameters(this->nextCommand, &commandObj);
            }
            else if (command == F(USB_ALARM_COMMAND_DEL_SENSOR))
            {
                commandObj.setCommand(ALARM_COMMAND_DEL_SENSOR);
                this->extractParameters(this->nextCommand, &commandObj);
            }
            else if (command == F(USB_ALARM_COMMAND_CHANGE_USER_CODE))
            {
                commandObj.setCommand(ALARM_COMMAND_CHANGE_USER_CODE);
                this->extractParameters(this->nextCommand, &commandObj);
            }
            else if (command == F(USB_ALARM_COMMAND_CHANGE_ADMIN_CODE))
            {
                commandObj.setCommand(ALARM_COMMAND_CHANGE_ADMIN_CODE);
                this->extractParameters(this->nextCommand, &commandObj);
            }
            else if (command == F(USB_ALARM_COMMAND_SENSOR_OFF))
            {
                commandObj.setCommand(ALARM_COMMAND_SENSOR_OFF);
                this->extractParameters(this->nextCommand, &commandObj);
            }
            else if (command == F(USB_ALARM_COMMAND_SENSOR_ON))
            {
                commandObj.setCommand(ALARM_COMMAND_SENSOR_ON);
                this->extractParameters(this->nextCommand, &commandObj);
            }
            else if (command == F(USB_ALARM_COMMAND_SENSOR_DELAYED))
            {
                commandObj.setCommand(ALARM_COMMAND_SENSOR_DELAYED);
                this->extractParameters(this->nextCommand, &commandObj);
            }
            else if (this->stringIsNumeric(command))
            {
                commandObj.setCommand(ALARM_COMMAND_NUMERIC_CODE);
                commandObj.setParameter(1, command);
            }
            
            this->lastCommand = commandObj;
            this->nextCommand = "";
        }
        else
        {
            this->nextCommand += key;
        }
    }
    
    return commandObj;
}

bool MatrixKeypadCommandPreprocessor::stringIsNumeric(String var)
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

String MatrixKeypadCommandPreprocessor::getCommandFromString(String inputString)
{
    unsigned int indexTo = (inputString.indexOf(' ') >= 0) ? inputString.indexOf(' ') : inputString.length();
    return inputString.substring(0, indexTo);
}

AlarmCommand MatrixKeypadCommandPreprocessor::getLastCommand()
{
    return this->lastCommand;
}

void MatrixKeypadCommandPreprocessor::extractParameters(String inputString, AlarmCommand* commandObj)
{
    String paramString = inputString.substring((inputString.indexOf(' ') >= 0) ? inputString.indexOf(' ')+1 : inputString.length());
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
