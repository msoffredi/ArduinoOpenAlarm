#include "LCDOutputProcessor.h"

#ifdef I2C_DISPLAY
LCDOutputProcessor::LCDOutputProcessor() 
    : LiquidCrystal_I2C(LCD_I2C_ADDRESS, LCD_ROWS, LCD_COLS) 
#else
LCDOutputProcessor::LCDOutputProcessor() 
    : LiquidCrystal(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7) 
#endif
{
    this->beginDone = false;
    this->mlBuffer = "";
}

void LCDOutputProcessor::println(AlarmOutput outputObj)
{
    if (!this->beginDone)
    {
        this->beginDone = true;
        
        // Customize to match your display setup needs
        #ifdef I2C_DISPLAY
        this->begin();
        this->backlight();
        #else
        this->begin(LCD_ROWS, LCD_COLS);
        #endif

    }
    
    uint8_t outputType = outputObj.getOutputType();
    
    switch (outputType)
    {
        case ALARM_OUTPUT_ARM:
        case ALARM_OUTPUT_DISARM:
        case ALARM_OUTPUT_TEXT:
            this->outputText(outputObj.getOutputText());
            break;            
    }
}

void LCDOutputProcessor::printml(AlarmOutput outputObj)
{
    // This can be refactored if we want to display multiple lines in a more
    // human readable way (scrolling for example).
    this->println(outputObj);
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
