# Aplicativo

Programa que, utilizando el sensor de ultrasonido HC-SR04, mide la distancia entre dicho sensor y un obstáculo, para luego repetir indefinidamente. Cada medición es reportada por el puerto serie del Arduino Nano, el cual se utiliza de la siguiente manera:
1. Se configura el puerto serie de la PC con el comando _stty -F /dev/ttyUSB0 speed 2400_
2. Se consultan las mediciones con el comando _cat /dev/ttyUSB0_

Nota: los tiempos de espera utilizados para realizar las mediciones dependen de la velocidad del procesador, el programa supone 16MHz.

# Instalación

Se necesita 1 HC-SR04, conectado de la siguiente manera al Arduino Nano:
- Pin VCC de HC-SR04 a pin 5V de Arduino Nano
- Pin GND de HC-SR04 a pin GND de Arduino Nano
- Pin ECHO a pin D8
- Pin TRIG a pin D10

Grabar en el Arduino Nano de la manera habitual con consola abierta en este directorio (ultrasonido):
1. make all
2. make flash

En caso de error, comprobar que el Arduino Nano esté correctamente conectado y que la variable PUERTO del Makefile coincida con el reportado por _ls /dev_, también probar cambiando variable BPS por 57600.

Importante: NO borrar el archivo serial.o, es el controlador utilizado por el Arduino Nano.