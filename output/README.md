# Alternative Output Options

This folder contains alternative output processors you can use for your alarm.
For obvious reasons we do not support all the output options available, but you 
can easily build your own.

## How to use an alternative output option

Alternative output options or Output Processors come in pair of files with the 
same name, one with extension .cpp and the other one with extension .h.
To use an alternative output processor you have to first copy the two files to 
the project root directory. After that edit the project main file 
ArduinoOpenAlarm.ino and change the lines:

```
#include "USBOutputProcessor.h"
USBOutputProcessor outP;
```

...to match the processor you want to use. For example for the LCD Output 
Processor the lines should be:

```
#include "LCDOutputProcessor.h"
LCDOutputProcessor outP;
```

Apart from that, most alternative output processors have custom configurations
you can (sometimes have to) change, like PIN numbers, communication addresses, 
etc. Always take a quick look at the .h file. They usually have enough in-line
information for configuration variables.

## LCD standard displays

These displays come in many different configurations including interfaces (like
I2C) and display capacity (like 16 rows x 2 columns). The Output processor can
easily be adapted to most market options.

