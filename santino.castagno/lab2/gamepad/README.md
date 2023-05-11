# Gamepad

Este programa utiliza los componentes colocados en la protoboard como dispositivos para manipular el juego OpenTyrian.
    1. Hace uso del potenciometro para mover la nave hacía la izquierda o la derecha.
    2. Utiliza el pulsador para disparar con la nave a los enemigos.
## Running Tests

Para probar el programa, ejecute los siguientes comandos:

```bash
  make clean
  make
  make flash
  make game
```

En caso de que no funcione, ejecutar:

```bash
  dmesg
```

Y observar cuál es la interfaz TTY asociada a la placa Arduino conectada por USB. Luego, cambiar dicha variable en el Makefile.

## Authors

- [@Santino Castagno](https://www.github.com/SantinoCastagno)
