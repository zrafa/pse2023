# Fotoresistencia
> Control del brillo de la pantalla de la notebook mediante el uso de una fotoresistencia.

***

## Software
> El objetivo del programa en leer la señal analógica de la fotoresistencia desde el ADC y en base al valor obtenido, se envia por el UART el valor correspondiente. El script `brightness.sh` recibe el valor por el puerto serial y mediante el uso del programa brightnessctl se modifica el brillo de la pantalla.

Makefile
```
make clean
make
make flash
```
***
## Hardware
- **Fotoresistencia LDR**
- **Resistencia 10k**

Señal analógica A0 en arduino nano.