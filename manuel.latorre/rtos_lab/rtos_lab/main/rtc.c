#include <xinu.h>
#include "serial.h"
#include "globals.h"
#include "timer1.h"
//volatile int initiated_motor=0;
int main_rtc(void)
{
  while(1){
    seconds++;
    sleep(1);
  }
}



