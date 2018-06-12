/*
 * How to use this alternative output processor:
 * 
 * 1) Add the following lines to the top of your ArduinoOpenAlarm.ino file:
 * 
 * #include <Wire.h>
 * #include "LiquidCrystal_I2C.h"
 * 
 * 2) Copy the following files to the project root directory:
 * 
 * LCDOutputProcessor.h
 * LCDOutputProcessor.cpp
 * 
 * 3) Replace the following lines of your ArduinoOpenAlarm.ino file:
 * 
 * #include "USBOutputProcessor.h"
 * USBOutputProcessor outP;
 *
 * with the following ones:
 * 
 * #include "LCDOutputProcessor.h"
 * LCDOutputProcessor outP;
 * 
 * 4) Edit the "EDITABLE AREA" on this file to match your LCD display. Only edit
 * where it says "I2C ONLY" if your display is I2C, and only edit "NON I2C ONLY"
 * if your display IS NOT I2C.
 *
 */

#ifndef LCDOUTPUTPROCESSOR_H
#define LCDOUTPUTPROCESSOR_H

#if defined(ARDUINO)
 #if ARDUINO >= 100
  #include <Arduino.h>
 #else
  #include <wiring.h>
 #endif 
#endif

// EDITABLE AREA (start)

// Change this to 0 if your display is not I2C
#define I2C_DISPLAY 1

//////////////
// I2C ONLY //
//////////////
// Change it to match your display address
#define LCD_I2C_ADDRESS 0x27

//////////////////
// NON I2C ONLY //
//////////////////

// Display number of rows
#define LCD_ROWS 16
// Display number of cols
#define LCD_COLS 2

// EDITABLE AREA (end)

#include "Wire.h"
#include "OutputProcessor.h"
#include "Language.h"

#ifdef I2C_DISPLAY
#include "LiquidCrystal_I2C.h" 
class LCDOutputProcessor : public OutputProcessor, public LiquidCrystal_I2C
#else 
#include "LiquidCrystal.h" 
class LCDOutputProcessor : public OutputProcessor, public LiquidCrystal
#endif /* I2C_DISPLAY */
{
private:
    bool beginDone;
    
    void outputText(String text);
    
public:
    LCDOutputProcessor();
    void processOutput(AlarmOutput outputObj);
    void processAlarmStatus(String statuses);
    
};

#endif /* LCDOUTPUTPROCESSOR_H */
