# Speaker

## Conexiones
Utiliza el puerto A2 para el potenciometro y el puerto D8 para el speaker.

## Funcionamiento
Obtiene del ADC del puerto A2 la leectura del potenciometro, la cual es de 12 bits, por ende va desde 0 a 4095, por lo tanto se divide dicho numero por 455 (para tener una escala de 0 a 9 mas facil de manejar).
Dependiendo de la entrada del potenciomentro, el tiempo de alto de la señal del speaker cambia, manteniendo el tiempo del periodo intacto para que suene la nota exacta. Dicho cambio del tiempo en alto hace que el volumen del speaker cambie, por lo tanto cuando mas grande sea el numero, mas fuerte sera el sonido, y cuanto mas chico, mas suave será.
