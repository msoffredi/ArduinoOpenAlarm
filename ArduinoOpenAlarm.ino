#include <EEPROM.h>
#include <RCSwitch.h>

// Language file for output texts
#include "Language.h"

#include "USBCommandPreprocessor.h"
USBCommandPreprocessor commPP;

// Standard USB Output Processor
#include "USBOutputProcessor.h"
USBOutputProcessor outP;

#include "OutputProcessor.h"
#include "Alarm.h"
#include "ArmedMode.h"
#include "DisarmedMode.h"
#include "EEPROMHandler.h"
#include "AlarmCommon.h"

EEPROMHandler eeprom;
Alarm alarm(&eeprom);
CommonAlarmSharedObjects common(&alarm, &commPP, &outP, &eeprom);
DisarmedMode dmode(&common);
ArmedMode amode(&common);

void setup() 
{
    Serial.begin(9600);
    while (!Serial);
        
    outP.processOutput(AlarmOutput(ALARM_OUTPUT_TEXT, F(TEXT_INITIALIZING)));

    // Initializing bell
    pinMode(BELL_PIN, OUTPUT);
    digitalWrite(BELL_PIN, !BELL_ACTIVE_PIN_SIGNAL);
    
    outP.processOutput(AlarmOutput(ALARM_OUTPUT_TEXT, F(TEXT_INIT_DONE)));

    pinMode(BEEPER_PIN, OUTPUT);
    OutputProcessor::beep();
    delay(500);
    OutputProcessor::beep(2);
}

void loop() 
{
    alarm.loop();
    
    if (alarm.getStatus() == ALARM_STATUS_DISARMED)
    {
        dmode.loop();
    }
    else if (alarm.getStatus() == ALARM_STATUS_ARMED)
    {
        amode.loop();
    }
}
