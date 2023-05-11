# Fotoresistencia

Este programa hace uso de la foto resistencia para manipular el brillo de la pantalla de una notebook.
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
