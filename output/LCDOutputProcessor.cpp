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
            this->outputText(outputObj.getOutputText());
            break;            
    }
}

void LCDOutputProcessor::outputText(String text)
{
    this->clear();

    if (text.indexOf('.') == -1)
    {
        this->print(text);
    }
    else if (text.indexOf('.', text.indexOf('.')+1) == -1)
    {
        this->print(text.substring(0, text.indexOf('.')));
        this->setCursor(0, 1);
        this->print(text.substring(text.indexOf('.')+2));
    }
    // TODO we should find a better way to display multiple lines 
    else
    {
        this->print(text);
    }
    
    // Make LCD display USB compatible
    Serial.println(text);
 }

void LCDOutputProcessor::processAlarmStatus(String statuses)
{
    this->processOutput(AlarmOutput(ALARM_OUTPUT_TEXT, statuses));
}

void LCDOutputProcessor::processBell(bool bellStatus)
{
    if (bellStatus == ALARM_BELL_ON)
    {
        // Customize your bell by activating here
        this->processOutput(AlarmOutput(ALARM_OUTPUT_TEXT, F("Bell is on")));
    }
    else if (bellStatus == ALARM_BELL_OFF)
    {
        // Customize your bell by deactivating here
        this->processOutput(AlarmOutput(ALARM_OUTPUT_TEXT, F("Bell is off")));
    }
}
