TTY=/dev/ttyACM0
#TTY=/dev/ttyUSB0

all:
	avr-gcc -c -o sleep.o sleep.c
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o led.o led.c
	avr-gcc -mmcu=atmega328p led.o -o led.elf sleep.o
	avr-objcopy -O ihex -R .eeprom led.elf led.hex

flash:
	sudo avrdude -v -v -v -v -p atmega328p -c arduino -P $(TTY) -b 115200 -D -U flash:w:led.hex:i
	
clean:
	rm led.elf led.o led.hex sleep.o