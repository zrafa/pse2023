# Ultrasonido y Knight Rider

Este programa cumple las siguientes funciones:
    1. Enciende el knight rider al presionar la tecla "k"
    2. Utiliza el ultrasound para medir la distancia a la que se encuentra un objeto en la dirección a la que se encuentra apuntando.
    
## Running Tests

Para probar el programa ejecute:

```bash
    make
```

En caso de que no funcione, ejecutar:

```bash
  dmesg
```

Y observar cuál es la interfaz TTY asociada a la placa Arduino conectada por USB. Luego, cambiar dicha variable en el Makefile.

## Authors

- [@Santino Castagno](https://www.github.com/SantinoCastagno)
