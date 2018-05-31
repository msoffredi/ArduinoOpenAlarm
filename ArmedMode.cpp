#include "ArmedMode.h"

ArmedMode::ArmedMode(Alarm* alarm, CommandPreprocessor* commPP, OutputProcessor* outP)
{
    this->userCode = DEFAULT_USER_CODE;
    this->alarm = alarm;
    this->commandPreprocessor = commPP;
    this->outProcessor = outP;
}

void ArmedMode::loop()
{
    AlarmCommand commandObj = this->commandPreprocessor->getNextCommand();
    
    if (commandObj.getCommand() != ALARM_COMMAND_NONE)
    {
        this->processCommand(commandObj);
    }
}

void ArmedMode::processCommand(AlarmCommand commandObj)
{
    uint8_t command = commandObj.getCommand();
    
    if (command == ALARM_COMMAND_ARM)
    {
        this->disarm(&commandObj);
    }
}

void ArmedMode::disarm(AlarmCommand* commandObj)
{
    String code = commandObj->getParameter(1);
    
    // TODO: add verification all sensors are inactive
    if (code.toInt() == this->userCode)
    {
        this->alarm->setStatus(ALARM_STATUS_DISARMED);
    }
}
