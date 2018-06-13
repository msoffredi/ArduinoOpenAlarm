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

## Options available

- LCDOutputProcessor: Output option for LCD displays of the type of those with
1, 2 or 4 lines, with 8-40 characters in their I2C and non I2C versions.
