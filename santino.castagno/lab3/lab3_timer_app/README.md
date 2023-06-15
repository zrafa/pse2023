# Servo with buttons

Este programa realiza las siguientes acciones:
    1. Al presionar los botones el servo cambia su posición. 
        1.1 Se utiliza el timer1 para emitir la senial pwm que permite manipular la posicion del servo.

### Observacion

Aparentemente, este servo se posiciona en:
    - 0° cuando la duracion de la senial en alto (duty) es de 0.0005 
    - 180° cuando la duracion de la senial en alto es de 0.0022

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
