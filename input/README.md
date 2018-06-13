# Alternative command preprocessor

This folder contains alternative command preprocessors you can use as an 
alternative input option for your alarm.
For obvious reasons we do not support all the available input options, but you 
can easily build your own.

## How to use an alternative command preprocessor

Alternative command preprocessors come in pair of files with the same name, one 
with extension .cpp and the other one with extension .h.
To use an alternative command preprocessor you have to first copy the two files 
to the project root directory. After that edit the project main file 
ArduinoOpenAlarm.ino and change the lines:

```
#include "USBCommandPreprocessor.h"
USBCommandPreprocessor commPP;
```

...to match the processor you want to use. For example for the keypad matrix 
command preprocessor the lines would be:

```
#include "MatrixKeypadCommandPreprocessor.h"
MatrixKeypadCommandPreprocessor commPP;
```

Apart from that, most alternative command preprocessors have custom 
configurations you can (sometimes have to) change, like PIN numbers, 
communication addresses, etc. 
Always take a quick look at the .h file. They usually have enough in-line
information for configuration variables.

## Options available

- MatrixKeypadCommandPreprocessor = Preprocessor for 3x4 & 4x4 matrix keypads 
with direct connection to the Arduino board (does not support I2C versions).
