
# hello_world

Este programa enciende y apaga tres leds de la placa (portb bit 0, 1 y 2) en loop, en función del pulsador (port bit 5).
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

