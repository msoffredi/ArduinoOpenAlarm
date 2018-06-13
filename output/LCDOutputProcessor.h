/*
 * How to use this alternative output processor:
 * 
 * First of all, if your LCD is an I2C version, you need to install a Library 
 * (if you don't already have it).
 * The library can be downloaded from here: 
 * https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library/archive/master.zip
 * 
 * And I recommend you go over at least one of the examples there to verify 
 * the library can handle your display. After that, follow the steps below:
 * 
 * 1) Add the following lines to the top of your ArduinoOpenAlarm.ino file:
 * 
 * 1a) If your LCD is I2C
 * #include <Wire.h>
 * #include "LiquidCrystal_I2C.h"
 * 
 * 1b) If your LCD is I2C
 * #include <Wire.h>
 * #include "LiquidCrystal.h"
 * 
 * 2) Copy the following files to the project root directory:
 * 
 * /output/LCDOutputProcessor.h
 * /output/LCDOutputProcessor.cpp
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
 * if your display IS NOT I2C. If your display is I2C also comment the line with:
 * 
 * #define I2C_DISPLAY
 *
 * Note: When using this output processor you should consider using minimized
 * versions of the Language.h file. See /languages/README.md 
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

// Comment this line if your display is not I2C
#define I2C_DISPLAY

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
// Display pins
#define LCD_RS 3
#define LCD_EN 4
#define LCD_D4 5
#define LCD_D5 6
#define LCD_D6 7
#define LCD_D7 8

// EDITABLE AREA (end)

#include "OutputProcessor.h"
#include "Wire.h"

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
    void processBell(bool bellStatus);
    
};

#endif /* LCDOUTPUTPROCESSOR_H */
