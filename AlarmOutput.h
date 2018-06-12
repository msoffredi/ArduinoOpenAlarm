#ifndef ALARMOUTPUT_H
#define ALARMOUTPUT_H

#if defined(ARDUINO)
 #if ARDUINO >= 100
  #include <Arduino.h>
 #else
  #include <wiring.h>
 #endif 
#endif

#define ALARM_OUTPUT_TEXT 0
#define ALARM_OUTPUT_ARM 2
#define ALARM_OUTPUT_DISARM 3

class AlarmOutput
{
private:
    uint8_t outputType;
    String outputText;
    
public:
    AlarmOutput(uint8_t otype = ALARM_OUTPUT_TEXT, String otext = "");
    void setOutputType(uint8_t otype);
    void setOutputText(String otext);
    uint8_t getOutputType();
    String getOutputText();
    
};

#endif /* ALARMOUTPUT_H */

