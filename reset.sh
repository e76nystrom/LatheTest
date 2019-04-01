#!/bin/bash

/cygdrive/c/Users/Eric/.platformio/packages/tool-avrdude/avrdude \
-D -v \
-p atmega2560 \
-b 115200 \
-P COM4 \
-C "C:\Users\Eric\.platformio\packages\tool-avrdude\avrdude.conf"

/cygdrive/c/DevSoftware/Putty/putty.exe -load COM4-19200
