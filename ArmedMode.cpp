#include "ArmedMode.h"

ArmedMode::ArmedMode(Alarm* alarm, CommandPreprocessor* commPP, OutputProcessor* outP, EEPROMHandler* eeprom)
{
    this->alarm = alarm;
    this->commandPreprocessor = commPP;
    this->outProcessor = outP;
    this->eeprom = eeprom;
    
    if (this->eeprom->isFirstTime())
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
    if (this->alarm->getBell())
    {
        this->outProcessor->processOutput(
                AlarmOutput(ALARM_OUTPUT_BELL, String(F(TEXT_ALARM_BELL_ON)))
                );
    }
    
    AlarmCommand commandObj = this->commandPreprocessor->getNextCommand();
    
    if (commandObj.getCommand() != ALARM_COMMAND_NONE)
    {
        this->processCommand(commandObj);
    }
}

void ArmedMode::processCommand(AlarmCommand commandObj)
{
    uint8_t command = commandObj.getCommand();
    
    if (command == ALARM_COMMAND_DISARM)
    {
        this->disarm(&commandObj);
    }
}

void ArmedMode::disarm(AlarmCommand* commandObj)
{
    String code = commandObj->getParameter(1);
    
    if (code.toInt() == this->userCode)
    {
        this->alarm->setStatus(ALARM_STATUS_DISARMED);
        
        this->outProcessor->processOutput(
                AlarmOutput(ALARM_OUTPUT_DISARM, String(F(TEXT_ALARM_DISARMED)))
                );
        
        if (this->alarm->getBell())
        {
            this->alarm->setBell(false);
            
            this->outProcessor->processOutput(
                    AlarmOutput(ALARM_OUTPUT_BELL, String(F(TEXT_ALARM_BELL_OFF)))
                    );
        }
    }
}
