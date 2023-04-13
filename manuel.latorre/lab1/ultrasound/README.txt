# Arduino UNO: colocamos el puerto serial a 9600 bpp (baudios/bits por segundo).
# Arduino NANO: colocamos el puerto serial a 2400 bpp (baudios/bits por segundo).
  stty -F /dev/ttyUSB0 speed 9600 #en caso de Arduino NANO 2400

# NO borrar serial.h ni serial.o

////EJECUCIÓN////
make clean (si ya habia archivos .o y .hex creados)
make (compilar)
make flash (cargar en Arduino)
cat /dev/ttyUSB0 #Imprime por consola lo que devuelve el ultrasonido

////Pines para conexión////
d8 = SALIDA (a trigger del ultrasound)
d11 = ENTRADA (a echo del ultrasound)