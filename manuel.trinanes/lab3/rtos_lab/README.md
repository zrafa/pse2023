# RTOS LAB (Xinu)

## Conexiones
Utiliza los puertos:
    - D9 para el servo
    - D10 para el motor cc
    - A2 para el knob

## Funcionamiento
Por el serial:
    - b: detiene el motor cc
    - n: reanuda el motor cc
    - a: mueve el servo a la izquierda
    - b: mueve el servo a la derecha

## Implementacion
Consta de 7 procesos:
    - null
    - main (ejecuta un metodo que prende y apaga el led de la placa)
    - servo (setea en el ocr1a los ticks de comparacion para el movimiento del servo)
    - knob (lee el knob y setea el ocr1b para satisfacer el % de velocidad seleccionado)
    - serial in (lee las entradas del usuario)
    - serial out (imprime por el serial el estado del hardware)
    - rtc (real time clock, aumenta en 1 una variable global cada un segundo)
