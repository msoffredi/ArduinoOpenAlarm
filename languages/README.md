# Arduino Open Alarm languages folder

This folder contains alternative Language.h files translated to other languages. 
It also has minimized versions in some cases for when you have to limit texts to 
a maximum number of characters (with some small LCD displays for example).

## File name syntax

- Language.AB.h means language represented by "AB" for example en = English, es = Español
- Language.min.AB.h means minimized version of the same Language.AB.h for small output media

Note: not all translations have a minimized versions 

## How to use a translation

Simply replace the file Language.h in the root folder by any of the translated 
version and make sure you rename your translated version to "Language.h". Compile
the project again and there you go!
