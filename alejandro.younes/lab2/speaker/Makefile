PUERTO=ttyUSB0
BPS=115200

APP=speaker.elf
OBJETOS=utils.o adc.o main.o

CC=avr-gcc
CFLAGS=-Os -DF_CPU=4000000UL -mmcu=atmega328p 
LDFLAGS=-mmcu=atmega328p
FIRMWARE=imagen.hex

# $@:Se sustituye por el nombre del objetivo de la presente regla.
# $*:Se sustituye por la raíz de un nombre de fichero.
# $<:Se sustituye por la primera dependencia de la presente regla.
# $^:Se sustituye por una lista separada por espacios de cada una de las dependencias de la presente regla.

all: $(APP)

$(APP): $(OBJETOS)
	$(CC) $(LDFLAGS) -o $@ $^ 

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

flash:
	avr-objcopy -O ihex -R .eeprom $(APP) $(FIRMWARE)
	avrdude -p atmega328p -c arduino -P /dev/$(PUERTO) -b $(BPS) -D -U flash:w:$(FIRMWARE):i

clean:
	rm utils.o adc.o main.o $(APP) $(FIRMWARE)
