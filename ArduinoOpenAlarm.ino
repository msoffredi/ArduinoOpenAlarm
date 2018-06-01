#include <EEPROM.h>
#include <RCSwitch.h>

// Language file for output texts
#include "Language.h"

#include "USBCommandPreprocessor.h"
USBCommandPreprocessor commPP;

#include "USBOutputProcessor.h"
USBOutputProcessor outP;

#include "Alarm.h"
#include "ArmedMode.h"
#include "DisarmedMode.h"
#include "EEPROMHandler.h"

EEPROMHandler eeprom;
Alarm alarm(&eeprom);
DisarmedMode dmode(&alarm, &commPP, &outP, &eeprom);
ArmedMode amode(&alarm, &commPP, &outP, &eeprom);

void setup() 
{
    Serial.begin(9600);
    while (!Serial);
    
    outP.processOutput(AlarmOutput(ALARM_OUTPUT_TEXT, F(TEXT_INITIALIZING)));
    // ...
    outP.processOutput(AlarmOutput(ALARM_OUTPUT_TEXT, F(TEXT_INIT_DONE)));
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
