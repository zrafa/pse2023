#include <xinu.h>
#include "serial.h"
#include "globals.h"
#include "timer1.h"
volatile int last_angle=0;
int main_servo(void)
{
  
  while(1){
    if(last_angle != serv_angle){
      timer1_servo(serv_angle);
      last_angle=serv_angle;
      //serial_put_int(last_angle,3);
    }
    sleepms(1);//Para que libere CPU y pueda correr main
  }
}




