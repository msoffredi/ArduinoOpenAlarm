#include "OutputProcessor.h"

#ifdef ALARM_BEEPER_AVAILABLE
void OutputProcessor::beep(uint8_t repetition, uint16_t repetitionDuration, uint16_t duration)
{
    for (uint8_t x=0; x<repetition; x++)
    {
        digitalWrite(BEEPER_PIN, LOW);
        delay(duration);
        digitalWrite(BEEPER_PIN, HIGH);
        
        if (x < repetition-1)
        {
            delay(repetitionDuration);
        }
    }
}
#endif
