#include <xinu.h>
#include "serial.h"
#include "globals.h"
#include "timer1.h"
//volatile int initiated_motor=0;
int main_show_data(void)
{
  unsigned int hour;
  unsigned int min;
  unsigned int seg;
  while(1){
    hour = seconds / 3600; // Calcula las horas completas en base a 3600 segundos por hora
    seg = seconds%3600; // Actualiza los segundos restantes después de calcular las horas
    min = seg / 60; // Calcula los minutos completos en base a 60 segundos por minuto
    seg = seg % 60; // Calcula los segundos restantes después de calcular los minutos
    serial_put_int(hour,2);
    serial_put_char(':');
    serial_put_int(min,2);
    serial_put_char(':');
    serial_put_int(seg,2);
    serial_put_str_inline(". velocidad: ");
    serial_put_int(motor_speed*10,3);
    serial_put_str_inline("%. servo:");
    serial_put_int(serv_angle,3);
    serial_put_str_inline(" grados.");
    serial_put_str(" ");//Esto me genera un salto de linea
    sleep(1);
  }
}



