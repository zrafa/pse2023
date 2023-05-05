# Gamepad

## Conexiones
Utiliza el puerto A2 para el potenciometro y el puerto D2 para el botón.

## Funcionamiento
Obtiene del ADC del puerto A2 la leectura del potenciometro, la cual es de 12 bits, por ende va desde 0 a 4095, por lo tanto se divide dicho numero por 455 (para tener una escala de 0 a 9 mas facil de manejar) y dividido por 3 para tener 3 regiones del potenciometro.
Dependiendo de la entrada del potenciometro, si se encuentra en la porcion de la izquierda, manda por serial una 'a', en el centro vacio y la derecha una 'd'.
Ademas, lee el puerto D2, en dicho puerto hay conectado un boton, y si es presionado envia por
serial una 's'.

## Modo de uso
Hacer uso del siguiente programa bash para correr en una terminal y poder usar el nuevo periferico
como una entrada de teclado mas:

sudo cat /dev/ttyUSB0 | while read -n 1 key; do xdotool key $key; done
