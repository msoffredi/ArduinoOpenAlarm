#include "OutputProcessor.h"

#ifdef ALARM_BEEPER_AVAILABLE
void OutputProcessor::beep(uint8_t repetition, uint16_t repetitionDuration, uint16_t duration)
{
    for (uint8_t x=0; x<repetition; x++)
    {
        digitalWrite(BEEPER_PIN, BEEPER_ACTIVE_PIN_SIGNAL);
        delay(duration);
        digitalWrite(BEEPER_PIN, !BEEPER_ACTIVE_PIN_SIGNAL);
        
        if (x < repetition-1)
        {
            delay(repetitionDuration);
        }
    }
}
#endif

void OutputProcessor::processBell(bool bellStatus)
{
    if (bellStatus)
    {
        digitalWrite(BELL_PIN, BELL_ACTIVE_PIN_SIGNAL);
    }
    else
    {
        digitalWrite(BELL_PIN, !BELL_ACTIVE_PIN_SIGNAL);
    }
}
