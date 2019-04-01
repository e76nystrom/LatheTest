#!/bin/bash

cp lathe.ino lathe.cpp

/cygdrive/c/Users/Eric/.platformio/packages/toolchain-atmelavr/bin/avr-g++ \
-c \
-fno-exceptions \
-fno-threadsafe-statics \
-fpermissive \
-std=gnu++11 \
-g \
-Os \
-Wall \
-ffunction-sections \
-fdata-sections \
-flto \
-mmcu=atmega2560 \
-DF_CPU=16000000L \
-DPLATFORMIO=030100 \
-DARDUINO_ARCH_AVR \
-DARDUINO_AVR_MEGA2560 \
-DARDUINO=10612 \
-I"C:\Users\Eric\.platformio\packages\framework-arduinoavr\cores\arduino" \
-I"C:\Users\Eric\.platformio\packages\framework-arduinoavr\variants\mega" \
-Isrc \
-o lathe.o \
--save-temps \
"lathe.cpp"

rm lathe.cpp
