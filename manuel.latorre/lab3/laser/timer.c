/*
  Genera 1000 interrupciones por segundo, utilizando el Timer 0 de 8bits
  1 milisegundo 1000 microsegundos

  utilizamos modo CTC, el cual compara con TOP, TOP es definido por 0CR0A.
  Cuando CONTADOR == TOP el CONTADOR se pone a cero.

  Reloj del sistema 4000000 de ticks/s / 64 (prescalar) = 62500 ticks/s

  62500 ticks/s / 62 = 1000 ticks/s =>
*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include "globals.h"
volatile int ticks = 0;
typedef struct
{
  uint8_t tccr0a; /* Registro de control A del timer0 */
  uint8_t tccr0b; /* Registro de control B del timer0 */
  uint8_t tcnt0; /* Registro timer/contador*/
  uint8_t ocr0a; /* Registor comparador A */
  uint8_t ocr0b; /* Registro comparador B */
}volatile timer0_t;

volatile timer0_t *timer0 = (timer0_t *)(0x44);

/* registro de mascara de interrupciones timer 0 */

volatile unsigned char *timer0_timsk0 = (unsigned char *)(0x6E);

#define TIMER0_CS 0x03 /* preescalar=64 CS02|CS01|CS00 = 0b001*/
#define TIMER0_CTC 0x02 /* CTC = WGM = 0b010 : modo CTC es comparar y volver a cero */

#define SYSTEM_TICKS 4000000
#define PRESCALAR 64
#define TICKS_PER_SECOND 1000

#define TIMER0_OCR0A (SYSTEM_TICKS/PRESCALAR/TICKS_PER_SECOND)

void timer0_init( void )
{
  timer0->tccr0a |= TIMER0_CTC;
  timer0->tccr0b |= TIMER0_CS;
  timer0->ocr0a = TIMER0_OCR0A;
  (*timer0_timsk0) |= 0x02;
  
}

/* rutina de atencion de interrupciones*/

ISR(TIMER0_COMPA_vect)
{
  ticks++;
  if(ticks==50){ 
    send=1;
    ticks=0;
  }
}