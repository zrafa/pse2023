
# Ultrasonido
> Control de un sensor digital de ultrasonido. Reporta via serial la distancia del objeto detectado, y a su vez se enciende unos leds, dependiendo de la distancia.

***

## Software
> El programa se basa en calcular la distancia respecto a un objeto mediante el ultrasonido. Para ello se envía un pulso de 10 us, y cuando el ultrasonido levanta la señal de high, se comienza a medir el tiempo para luego poder calcular la distancia. También se reporta este dato mediante puerto serial.

> La hoja de datos del ultrasonido HC-SR04 especifíca que la distancia es calculada mediante tiempo_us/58 pero para mayor precisión se modifico a tiempo_us/41, cálculo que presenta valores más precisos para el rango de interés del programa.

Mostrar distancia mediante puerto serial:
```
stty -F /dev/ttyUSB0 speed 2400
cat /dev/ttyUSB0
```

Indicación de distancia mediante leds:
```
- Led 1: 10 cm o menos.
- Led 1 a 2: entre 10 a 20 cm.
- Led 1 a 3; entre 20 a 30 cm.
- Led 1 a 4: entre 30 a 50 cm.
- Leds apagados: distancias mayores a 50 cm.
```

Makefile
```
make clean
make
make flash
```

***

## Hardware

**Ultrasonido**:
- Trigger - PB1 (D9)
- Echo - PB0 (D8)
- VCC - 5V

**Leds**:
- PD2 (D2)
- PD3 (D3)
- PD4 (D4)
- PD5 (D5)


