#include "USBOutputProcessor.h"

void USBOutputProcessor::println(AlarmOutput outputObj)
{
    uint8_t outputType = outputObj.getOutputType();
    
    switch (outputType)
    {
        case ALARM_OUTPUT_ARM:
        case ALARM_OUTPUT_DISARM:
        case ALARM_OUTPUT_TEXT:
            Serial.println(outputObj.getOutputText());
            break;            
    }
}

void USBOutputProcessor::printml(AlarmOutput outputObj)
{
    this->println(outputObj);
}

void USBOutputProcessor::processAlarmStatus(String statuses)
{
    this->processOutput(AlarmOutput(ALARM_OUTPUT_TEXT, String(TEXT_ALARM_STATUS) + statuses));
}
