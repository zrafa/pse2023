#include "adc.h"
#include "serial.h"
#include "sleeps.h"

main(void)
{
  adc_init();
  serial_init();
  int val;

  while(1){
    val = adc_get(2); 
    //el maximo valor que soporta el brillo es 937
    if(val>937){
        val = 937;
    }
    serial_put_int(val, 3);
    serial_put_string("\n\r");
    sleep_ms(1200);
  }
  
}