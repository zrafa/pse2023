
# Pulsaciones
> Envio de pulsaciones de teclas de la computadora al sistema embebido para el control de knigth rider y sensor digital de ultrasonido que reporta via serial la distancia del objeto detectado.

***

## Software
> El programa recibe teclas que el usuario va enviando para determinar su accionar. Si se presiona la letra 'k' se controla el knigth rider (juego de luces con tres leds) y si se presiona la letra 'q' se toma una medida con el ultrasonido (se basa en calcular la distancia respecto a un objeto mediante el ultrasonido, reportando este dato mediante el puerto serial).

> En caso del ultrasonido la distancia se envia mediante un string y se lo visualiza por el programa `screen`.

Makefile
```
make clean
make
make flash
```

Para envio y recepción de bytes por el puerto serial:
```
screen /dev/ttyUSB0 2400
```

***

## Hardware

**Ultrasonido**:
- Trigger - PB1 (D9)
- Echo - PB0 (D8)
- VCC - 5V

**Leds**:
- PB2 (D10)
- PB3 (D11)
- PB4 (D12)