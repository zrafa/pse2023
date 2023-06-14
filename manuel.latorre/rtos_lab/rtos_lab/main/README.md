SE DESARROLLO CON ARDUINO PRO MINI
MOTOR: conectarlo a pb1 (pin 9), para esto se utiliza pwm con registro a
SERVO: conectarlo a pb2 (pin 10), para esto utiliza pwm con registro b
LED TESTIGO: Es el led de la placa pb5 (pin 13)

EJECUCION:
en rtos_lab/compile hacer make clean
make
make flash
desde consola ejecutar screen a screen /dev/ttyUSB0 9600 (Siempre a 9600 por mas que se use el arduino chino)