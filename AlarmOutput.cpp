#include "AlarmOutput.h"

AlarmOutput::AlarmOutput(uint8_t otype, String otext)
{
    this->setOutputType(otype);
    this->setOutputText(otext);
}

void AlarmOutput::setOutputType(uint8_t otype)
{
    this->outputType = otype;
}

void AlarmOutput::setOutputText(String otext)
{
    this->outputText = otext;
}

uint8_t AlarmOutput::getOutputType()
{
    return this->outputType;
}

String AlarmOutput::getOutputText()
{
    return this->outputText;
}
