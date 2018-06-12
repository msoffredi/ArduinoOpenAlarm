#include "LCDOutputProcessor.h"

LCDOutputProcessor::LCDOutputProcessor() 
    : LiquidCrystal_I2C(LCD_I2C_ADDRESS, LCD_ROWS, LCD_COLS) 
{
    this->beginDone = false;
}

void LCDOutputProcessor::processOutput(AlarmOutput outputObj)
{
    if (!this->beginDone)
    {
        this->beginDone = true;
        
        // Customize to match your display setup needs
        #ifdef I2C_DISPLAY
        this->begin();
        this->backlight();
        #else
        this->begin(LCD_ROWS, LCD_COLS)
        #endif

    }
    
    uint8_t outputType = outputObj.getOutputType();
    
    switch (outputType)
    {
        case ALARM_OUTPUT_ARM:
        case ALARM_OUTPUT_DISARM:
        case ALARM_OUTPUT_BELL:
        case ALARM_OUTPUT_TEXT:
            this->clear();
            this->print(outputObj.getOutputText());
            Serial.println(outputObj.getOutputText());
            break;            
    }
}

void LCDOutputProcessor::processAlarmStatus(String statuses)
{
    this->processOutput(AlarmOutput(ALARM_OUTPUT_STATUS, statuses));
}
