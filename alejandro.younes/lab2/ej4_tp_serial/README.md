# Aplicativo

Programa que al pulsar la tecla 'K' en la PC inicia/detiene el programa *knight_rider* del lab1 y al pulsar la tecla 'U' en la PC toma una medición de distancia con el programa *ultrasonido* del lab1.

Como sólo un programa puede estar funcionando a la vez entonces se debe detener el Knight Rider si se desea tomar una medición con el ultrasonido.

Para que la PC pueda enviar pulsaciones y recibir mediciones se debe ejecutar *tio -b 2400 /dev/ttyUSB0* en una consola abierta en cualquier directorio.

# Instalación

Se requieren 3 LEDs, 3 resistencias de 220 ohm y 1 HC-SR04, conectados de la siguiente manera al Arduino Nano:
- Ánodo del 1er LED a pin D10, cátodo a pin GND. Con 1er resistencia en serie entre ánodo y D10
- Ánodo del 2do LED a pin D11, cátodo a pin GND. Con 2da resistencia en serie entre ánodo y D11
- Ánodo del 3er LED a pin D12, cátodo a pin GND. Con 3ra resistencia en serie entre ánodo y D12
- Pin VCC de HC-SR04 a pin 5V de Arduino Nano
- Pin GND de HC-SR04 a pin GND de Arduino Nano
- Pin ECHO a pin D8
- Pin TRIG a pin D9

Grabar en el Arduino Nano de la manera habitual con consola abierta en este directorio (ej4_tp_serial):
1. make all
2. make flash

En caso de error, comprobar que el Arduino Nano esté correctamente conectado y que la variable PUERTO del Makefile coincida con el reportado por _ls /dev_, también probar cambiando variable BPS por 57600.

En la PC se debe tener instalada la aplicación *tio* (obtenible desde repositorios de Linux), en teoría cualquier otra aplicación para comunicarse por puerto serie debería funcionar.