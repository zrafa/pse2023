#include "timer.h"
#include "serial.h"
#include "adc.h"
#include <avr/interrupt.h>

void sleep_ms(unsigned int tiempo)
{
    volatile long i;
    for(i = 0; i < tiempo * 180; i++){
    }
}

//el servo se para en 720
/*El servo se mueve en sentido horario con velocidades de 520 a 720*/
/*El servo se mueve en sentido antihorario en velocidades de 720 a 920*/
/*El servo se conecta en el pin D9*/
void main()
{
  timer1_init();
  serial_init(); 
  adc_init();

  int velocidad_inicial = 920;
  int val;
  
  while(1){
     /* determinamos la velocidad y direccion*/
    val =  velocidad_inicial - ((adc_get(2)/150)*20); /* obtener una conversión ADC del pin de entrada ADC 2 */
    velocidad(val);
    sleep_ms(1000);
  }
  for(;;);
}

void velocidad(int vel){
    serial_put_string("\n\r servo a velocidad: ");
    serial_put_int(vel,4);
    timer1_rotacion_servo(vel);
    sleep_ms(1000);
}

