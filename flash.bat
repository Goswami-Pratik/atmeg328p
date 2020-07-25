if not exist bin md bin

avr-gcc -g -Os -mmcu=atmega328p -o bin/main.bin main.c

if errorlevel 1 (
  goto end
)

avr-objcopy -j .text -j .data -O ihex bin/main.bin bin/main.hex
rem avrdude -C"C:\WinAVR-20100110\bin\avrdude.conf" -pm328p -carduino -P %1 -b57600 -Uflash:w:"main.hex":i
avrdude -pm328p -carduino -P %1 -b57600 -Uflash:w:"bin/main.hex":i
avr-size bin/main.hex
EXIT /B 0

:end
EXIT /B %ERRORLEVEL%