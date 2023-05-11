CC=avr-gcc
OBJETOS=main.o serial.o sleep.o adc.o
APP=serial
CFLAGS=-Os -DF_CPU=16000000UL -mmcu=atmega328p 
LDFLAGS=-mmcu=atmega328p
FIRMWARE=imagen.hex
TTY=/dev/ttyACM0
# TTY=/dev/ttyUSB0

# $@:Se sustituye por el nombre del objetivo de la presente regla.
# $*:Se sustituye por la raíz de un nombre de fichero.
# $<:Se sustituye por la primera dependencia de la presente regla.
# $^:Se sustituye por una lista separada por espacios de cada una de las dependencias de la presente regla.

# F_CPU es el valor que se debe reemplazar en el fuente del serial

all: $(APP)
	make flash

$(APP): $(OBJETOS)
	$(CC) $(LDFLAGS) -o $@ $^ 

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

flash:
	avr-objcopy -O ihex -R .eeprom $(APP) $(FIRMWARE)
	sudo avrdude -p atmega328p -c arduino -P $(TTY) -b 115200 -D -U flash:w:$(FIRMWARE):i F_CPU 16000000

read:
	sudo cat $(TTY)

screen:
	screen $(TTY) 9600

clean:
	rm $(APP) $(FIRMWARE) $(OBJETOS)

game: 
	sudo ./game.sh
	
