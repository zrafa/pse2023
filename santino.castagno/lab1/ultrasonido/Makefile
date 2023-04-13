CC=avr-gcc
OBJETOS=main.o serial.o sleep.o
APP=encoder_test
CFLAGS=-Os -DF_CPU=16000000UL -mmcu=atmega328p 
LDFLAGS=-mmcu=atmega328p
FIRMWARE=imagen.hex
TTY=/dev/ttyACM0
#TTY=/dev/ttyUSB0

# $@:Se sustituye por el nombre del objetivo de la presente regla.
# $*:Se sustituye por la raíz de un nombre de fichero.
# $<:Se sustituye por la primera dependencia de la presente regla.
# $^:Se sustituye por una lista separada por espacios de cada una de las dependencias de la presente regla.

all: $(APP)
	make flash
	make read

$(APP): $(OBJETOS)
	$(CC) $(LDFLAGS) -o $@ $^ 

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

flash:
	avr-objcopy -O ihex -R .eeprom $(APP) $(FIRMWARE)
	sudo avrdude -p atmega328p -c arduino -P $(TTY) -b 115200 -D -U flash:w:$(FIRMWARE):i

read:
	sudo stty -F $(TTY) speed 9600
	sudo cat $(TTY)

clean:
	rm main.o $(APP) $(FIRMWARE) sleep.o
