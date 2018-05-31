#include "AlarmCommand.h"

AlarmCommand::AlarmCommand()
{
    this->command = ALARM_COMMAND_NONE;
    this->clearParameters();
}

uint8_t AlarmCommand::getCommand()
{
    return this->command;
}

// Index starts at 1 for parameters, so first parameter is 1 (not 0)
String AlarmCommand::getParameter(uint8_t index)
{
    // Be careful index is not validated for memory usage reduction
    return this->parameters[index-1];
}

void AlarmCommand::setCommand(uint8_t command)
{
    this->command = command;
}

// Index starts at 1 for parameters, so first parameter is 1 (not 0)
void AlarmCommand::setParameter(uint8_t index, String value)
{
    // Be careful index is not validated for memory usage reduction
    this->parameters[index-1] = value;
}

void AlarmCommand::clearParameters()
{
    for (int x=0; x<MAX_COMMAND_PARAMETERS; x++)
    {
        this->parameters[x] = "";
    }
}
