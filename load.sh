#!/bin/bash

#./avrdude -v -q -V -p32MX795F512L -Cavrdude.conf -D -cstk500v2 -b115200 -PCOM9 -Uflash:w:build-mega_pic32/ntp.hex:i

/cygdrive/c/Users/Eric/.platformio/packages/tool-avrdude/avrdude \
-D -v \
-p atmega2560 \
-C "C:\Users\Eric\.platformio\packages\tool-avrdude\avrdude.conf" \
-c wiring \
-b 115200 \
-P COM9 \
-U flash:w:.pio/build/megaatmega2560/firmware.hex:i

/cygdrive/c/DevSoftware/Putty/putty.exe -load COM9-19200
