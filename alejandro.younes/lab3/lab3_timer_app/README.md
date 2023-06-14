# Aplicativo

Programa que controla con precisión el ángulo de un servo utilizando el timer1 de un Arduino Nano, se utiliza la tecla **a** para girarlo a la izquierda de a 1 grado (con tope de 0 grados) y la tecla **d** para girarlo a la derecha de a 1 grado (con tope de 180 grados). Al iniciar el programa el servo se coloca automáticamente en 0 grados.

Para que la PC pueda enviar pulsaciones se debe ejecutar *tio -b 9600 /dev/ttyUSB0* en una consola abierta en cualquier directorio.

# Instalación

Se requiere 1 servo SG9 conectado de la siguiente manera al Arduino Nano:
- Pin GND del servo al pin GND del Arduino Nano
- Pin VCC del servo al pin 5V del Arduino Nano
- pin PWM del servo al pin D9 del Arduino Nano

Grabar en el Arduino Nano de la manera habitual con consola abierta en este directorio (lab3_timer_app):
1. make all
2. make flash

En caso de error, comprobar que el Arduino Nano esté correctamente conectado y que la variable PUERTO del Makefile coincida con el reportado por _ls /dev_, también probar cambiando variable BPS por 57600.

En la PC se debe tener instalada la aplicación *tio* (obtenible desde repositorios de Linux), en teoría cualquier otra aplicación para comunicarse por puerto serie debería funcionar.