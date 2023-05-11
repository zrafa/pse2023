# Aplicativo

Programa que utilizando un speaker hace sonar la canción del feliz cumpleaños y permite alterar las frecuencias sonoras del mismo (haciendo que suene de normal a muy grave) girando un potenciometro.

# Instalación

Se requieren 1 speaker y 1 potenciometro, conectados de la siguiente manera al Arduino Nano:
- Pin izquierdo de potenciometro a pin GND de Arduino Nano
- Pin medio de potenciometro a pin A0 de Arduino Nano
- Pin derecho de potenciometro a pin 5V de Arduino Nano
- Cable negro de speaker a pin GND de Arduino Nano
- Cable rojo de speaker a pin D8 de Arduino Nano

Grabar en el Arduino Nano de la manera habitual con consola abierta en este directorio (knight_rider):
1. make all
2. make flash

En caso de error, comprobar que el Arduino Nano esté correctamente conectado y que la variable PUERTO del Makefile coincida con el reportado por _ls /dev_, también probar cambiando variable BPS por 57600.