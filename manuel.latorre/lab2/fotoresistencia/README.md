////EJECUCIÓN////
make clean (si ya habia archivos .o y .hex creados)
make (compilar)
make flash (cargar en Arduino)
Una vez flasheado ejecutar brightnessctl.sh (Quizas sea necesario ejecutar primero screen para que arranque)

////Pines para conexión////
A0 = ENTRADA ANALOGICA (Entre la resistencia y la fotoresistencia, ambas deben ser de la misma impedancia)
