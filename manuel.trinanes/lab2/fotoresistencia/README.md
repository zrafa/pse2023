# Fotoresistencia

## Conexiones
Utiliza el puerto A2 para la resistencia, utilice ademas una resistencia de 2,2k.

## Funcionamiento
Obtiene del ADC del puerto A2 la leectura de la fotoresistencia, la cual es de 12 bits, por ende va desde 0 a 4095, pero como mi monitor tiene un maximo de 950 y el minimo para que no se apage por completo es de 100, le puse un if y le sume 100 al valor leido por la fotoresistencia para un uso mas util.

## Modo de uso
Hacer uso del siguiente programa bash para correr en una terminal root:

sudo cat /dev/ttyUSB0 | while read -n 3 num; do brightnessctl s $num; done
