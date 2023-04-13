
# ultrasonido

Este programa utiliza el sensor de ultrasonido HC-SR04 para sensar un objeto que tiene delante y calcular la distancia apróximada hacía dicho objeto. Utiliza el *portb bit 0* para emitir la señal que activar el sensor y el *portb bit 1* para captar la señal de echo del sensor.

Una aclaración importante que es particular en mi entrega: la función que utilizo para obtener la distancia a partir del tiempo es dividir los microsegundos esperados, en los que la señal de echo está en alto, por 46 en lugar de por 58. Ya que me dio valores más precisos para las mediciones realizadas en distancias de pocos centimetros.
## Running Tests

Para probar el programa, ejecute los siguientes comandos:

```bash
  make clean
  make
```

En caso de que no funcione, ejecutar:

```bash
  dmesg
```

Y observar cuál es la interfaz TTY asociada a la placa Arduino conectada por USB. Luego, cambiar dicha variable en el Makefile.
## Authors

- [@Santino Castagno](https://www.github.com/SantinoCastagno)

