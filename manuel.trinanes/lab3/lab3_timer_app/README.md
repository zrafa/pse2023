# Lector Laser

## Conexiones
Utiliza el puerto A2 para la fotoresistencia. 

## Funcionamiento
Obtiene del ADC del puerto A2 la leectura de la fotoresistencia, la cual es de 12 bits, por ende va desde 0 a 4095, y dependiendo de la resistencia, si esta es mas alta que un limite ambiente entonces detecta que se esta reciviendo algo, segun la secuencia de parpadeos es el caracter recivido.
Ambas implementaciones, de envio y recepcion, se encuentran en el laser.c, pero la recepcion fue hecha y probada para satisfacer el envio propuesto por Manuel Latorre
