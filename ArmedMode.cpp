#include "ArmedMode.h"

ArmedMode::ArmedMode(CommonAlarmSharedObjects* common)
{
    this->common = common;
    
    if (this->common->eeprom->isFirstTime())
    {
        this->userCode = DEFAULT_USER_CODE;
    }
    else
    {
        EEPROM.get(EEPROM_USER_CODE, this->userCode);
    }
}

void ArmedMode::loop()
{
    if (this->common->eeprom->getMessage() == MESSAGE_READ_USER_CODE)
    {
        EEPROM.get(EEPROM_USER_CODE, this->userCode);
        this->common->eeprom->setMessage(MESSAGE_NONE);
    }
    
    if (this->common->alarm->getBell())
    {
        this->ringBell();
    }
    
    AlarmCommand commandObj = this->common->commPP->getNextCommand();
    
    if (commandObj.getCommand() != ALARM_COMMAND_NONE)
    {
        this->processCommand(commandObj);
    }
}

void ArmedMode::ringBell()
{
    this->common->outP->processBell(ALARM_BELL_ON);
}

void ArmedMode::processCommand(AlarmCommand commandObj)
{
    uint8_t command = commandObj.getCommand();
    
    if (command == ALARM_COMMAND_DISARM)
    {
        this->disarm(&commandObj);
    }
    else if (command == ALARM_COMMAND_NUMERIC_CODE)
    {
        commandObj.setCommand(ALARM_COMMAND_DISARM);
        this->disarm(&commandObj);
    }
}

void ArmedMode::disarm(AlarmCommand* commandObj)
{
    String code = commandObj->getParameter(1);
    
    if (code.toInt() == this->userCode)
    {
        this->common->alarm->setBell(false);
        this->common->outP->processBell(ALARM_BELL_OFF);
        
        this->common->alarm->setStatus(ALARM_STATUS_DISARMED);
        
        this->common->outP->processOutput(
                AlarmOutput(ALARM_OUTPUT_DISARM, String(F(TEXT_ALARM_DISARMED)))
                );
        
        delay(200);
        OutputProcessor::beep(BEEP_COMMAND_ACCEPTED_REPETITIONS);
    }
    else
    {
        OutputProcessor::beep(1, 0, BEEP_COMMAND_ERROR_DURATION);
    }
}
