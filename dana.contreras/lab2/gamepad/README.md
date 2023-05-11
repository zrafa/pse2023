
# Gamepad
> Control de un pulsador y un knob para convertir el sistema embebido en un gamepad, de esta manera se controla de manera básica un videojuego en la PC Linux (movimiento de izquierda a derecha más disparo).

***

## Software
> El objetivo del programa se basa en presionar un pulsador y utilizar un potenciómetro para enviar bytes a la computadorra. En este caso, el script `gamepad.sh` recibe esos bytes y en base al contenido se determina si se debe presionar la tecla izquierda, derecha o espacio, utilizando la herramienta xdotool. El script en cuestión también se encarga de abrir la pagina del videojuego a probar en el navegador Chrome.

Makefile
```
make clean
make
make flash
```

Script
```
chmod +x gamepad.sh
./gamepad.sh
```

## Hardware

**Pulsador**:
- PB1 (D8 en Arduino).

**Potenciómetro**:
- Señal analógica (A0).
