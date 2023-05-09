////EJECUCIÓN////
make clean (si ya habia archivos .o y .hex creados)
make (compilar)
make flash (cargar en Arduino)
Una vez flasheado dar permisos en caso de ser necesario y ejecutar input.sh

////Pines para conexión////
d8,d9,d10 = SALIDAS KNIGHTRAIDER (Una para cada led)
d12 = SALIDA ULTRASOUND (Este va a trigger)
d11 = ENTRADA ULTRASOUND (Este va a echo)

