#!/bin/bash

./setup.py
cp lathe.ino src/lathe.cpp
cp *.cpp src/
cp *.h src/
HOME=C:/Users/Eric platformio run
avr-objdump.exe -l -d .pioenvs/megaatmega2560/firmware.elf >latheMega.lst
# avr-objdump.exe -l -d .pioenvs/pro16MHzatmega328/firmware.elf >latheMini.lst
# avr-objdump.exe -l -d .pioenvs/sparkfun_promicro16/firmware.elf >latheProMicro.lst
