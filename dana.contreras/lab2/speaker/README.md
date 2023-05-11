
# Speaker
> Control de un speaker interno para emitir sonidos a distinto volumen.

***

## Software
> El objetivo del programa se basa en aumentar el volumen de la canción que se está reproduciendo en bucle utilizando un potenciómetro y el driver para adc. Cada nota musical tiene una determinada frecuencia, por lo tanto el programa mantiene dicha frecuencia pero se modifica el tiempo en que la señal se encuentra en alto y bajo para aumentar o bajar el volumen de cada nota en base al valor del potenciómetro.

Makefile
```
make clean
make
make flash
```

## Hardware
**Internal speaker**:
- PB0 (D8 en Arduino).

