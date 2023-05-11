# Speaker & potenciometro

Este programa realiza las siguientes acciones:
    1. Hace que suene en el speaker la canción de "Happy Birthday".
    2. Permite que, mediante el potenciometro, se manipule el volumen de los sonidos que emite el speaker.

# Observacion

Para bajar y subir el volumen del speaker es necesario alternar el tiempo que la señal está en alto entré 0us y 10us. Esto implica que, el resto del tiempo de duración de la nota, la señal debería estar en bajo.

Por ejemplo, para la nota **do**, si buscamos que el volumen esté a la mitad:
```sh
    do_value = 191
    signal_h = 5
    signal_l = (do_value * 2) - signal_h = 377
```

## Running Tests

Para probar el programa, ejecute los siguientes comandos:

```bash
  make clean
  make
  make flash
```

En caso de que no funcione, ejecutar:

```bash
  dmesg
```

Y observar cuál es la interfaz TTY asociada a la placa Arduino conectada por USB. Luego, cambiar dicha variable en el Makefile.

## Authors

- [@Santino Castagno](https://www.github.com/SantinoCastagno)
