# Aplicativo

Programa de prueba que enciende 1 segundo y apaga 1 segundo el LED L de la placa Arduino Nano, para luego repetir indefinidamente.

Nota: la velocidad de encendido/apagado del LED depende de la velocidad del procesador, el programa supone 16MHz.

# Instalación

Grabar en el Arduino Nano de la manera habitual con consola abierta en este directorio (hello_world):
1. make all
2. make flash

En caso de error, comprobar que el Arduino Nano esté correctamente conectado y que la variable PUERTO del Makefile coincida con el reportado por _ls /dev_, también probar cambiando variable BPS por 57600.