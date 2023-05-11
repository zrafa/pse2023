# Aplicativo

Programa que según la luz recibida por una fotorresistencia varía el nivel de brillo del monitor de la PC, a mayor luz el nivel de brillo es mayor.

Para que la PC pueda cambiar el brillo se debe ejecutar *bash brillo.sh* en una consola abierta en este directorio (fotoresistencia).

Nota: La PC utilizada para programar varía su brillo entre 0 a 7267, como los valores leidos por el Arduino Nano van de 0 a 4095 y se debe enviar un entero entonces se reciben valores entre 0 y 8190.

# Instalación

Se requieren 1 resistencia de 220 ohm, 1 fotorresistor y 1 cable, conectados de la siguiente manera:
- pata izquierda de la resistencia a pin GND de Arduino Nano
- pata derecha de la resistencia a pata izquierda de la fotorresistencia
- pata derecha de la fotorresistencia a pin 5V de Arduino Nano
- un extremo del cable a pin A0 de Arduino Nano
- El otro extremo del cable entre la resistencia y la fotoresistencia

Grabar en el Arduino Nano de la manera habitual con consola abierta en este directorio (fotoresistencia):
1. make all
2. make flash

En caso de error, comprobar que el Arduino Nano esté correctamente conectado y que la variable PUERTO del Makefile coincida con el reportado por _ls /dev_, también probar cambiando variable BPS por 57600.

En la PC se debe tener instalada la aplicación *brightnessctl* (obtenible desde repositorios de Linux).