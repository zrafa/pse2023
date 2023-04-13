# Aplicativo

Programa que, al pulsar botón, enciende y apaga 3 LEDs en orden secuencial dejando siempre encendido sólo uno de ellos para luego repetir indefinidamente, busca imitar https://www.youtube.com/watch?v=sCTPbokUKBQ.

Se puede pulsar el botón en cualquier momento para detener el programa y luego pulsar en cualquier otro momento para volver a iniciarlo.

# Instalación

Se requieren 3 LEDs, 3 resistencias de 220 ohm y 1 pulsador, conectados de la siguiente manera al Arduino Nano:
- Ánodo del 1er LED a pin D10, cátodo a pin GND. Con 1er resistencia en serie entre ánodo y D10
- Ánodo del 2do LED a pin D11, cátodo a pin GND. Con 2da resistencia en serie entre ánodo y D11
- Ánodo del 3er LED a pin D12, cátodo a pin GND. Con 3ra resistencia en serie entre ánodo y D12
- Un pin del pulsador a D8 y otro pin del pulsador (que no esté conectado internamente al anterior) a GND

Grabar en el Arduino Nano de la manera habitual con consola abierta en este directorio (knight_rider):
1. make all
2. make flash

En caso de error, comprobar que el Arduino Nano esté correctamente conectado y que la variable PUERTO del Makefile coincida con el reportado por _ls /dev_, también probar cambiando variable BPS por 57600.