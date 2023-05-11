# Aplicativo

Programa que simula un gamepad para el juego *chromium-bsu*, utilizando un potenciometro que al estar girado a la izquierda equivale a presionar la flecha izquierda, al estar en posición intermedia equivale a no pulsar ninguna flecha y al estar girado a la derecha equivale a presionar la flecha derecha. Además un botón simula la pulsación de la tecla espacio (utilizada para disparar en el juego).

Para que la PC reciba las pulsaciones se debe ejecutar *bash gamepad.sh* en una consola abierta en este directorio (gamepad).

# Instalación

Se requiere 1 pulsador y 1 potenciometro, conectados de la siguiente manera al Arduino Nano:
- Un pin del pulsador a D8 y otro pin del pulsador (que no esté conectado internamente al anterior) a GND
- Pin izquierdo de potenciometro a pin GND de Arduino Nano
- Pin medio de potenciometro a pin A0 de Arduino Nano
- Pin derecho de potenciometro a pin 5V de Arduino Nano

Grabar en el Arduino Nano de la manera habitual con consola abierta en este directorio (gamepad):
1. make all
2. make flash

En caso de error, comprobar que el Arduino Nano esté correctamente conectado y que la variable PUERTO del Makefile coincida con el reportado por _ls /dev_, también probar cambiando variable BPS por 57600.

En la PC se debe tener instalada la aplicación *xdotool* y el juego *chromium-bsu* (obtenibles desde repositorios de Linux).