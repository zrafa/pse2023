#include "adc.h"
#include "serial.h"
#include "sleep.h"
main(void)
{
  int analog_in;
  adc_init();
  serial_init();
  while(1){
    analog_in = (adc_get(0)/455); //8bits = (adc_get(0)/28), 12 bits= (adc_get(0)/455)
    sleep_ms(400);
    sleep_ms(400);
    serial_put_int(analog_in, 4);
    serial_put_string("\n\r");
  }
}