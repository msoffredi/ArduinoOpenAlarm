#ifndef COMMANDPREPROCESSOR_H
#define COMMANDPREPROCESSOR_H

#if defined(ARDUINO)
 #if ARDUINO >= 100
  #include <Arduino.h>
 #else
  #include <wiring.h>
 #endif 
#endif
 
#include "AlarmCommand.h"

class CommandPreprocessor
{
protected:
    AlarmCommand lastCommand;
    
public:
    virtual AlarmCommand getNextCommand() = 0;
    virtual AlarmCommand getLastCommand() = 0;
    
};

#endif /* COMMANDPREPROCESSOR_H */
