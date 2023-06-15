#include <avr/interrupt.h>
#include <avr/io.h>
#include "globales.h"

typedef struct
{
    uint8_t tccr1a;
    uint8_t tccr1b;
    uint8_t tccr1c;
    uint8_t reserved;
    uint16_t tcnt1;
    uint16_t icr1;
    uint16_t ocr1a;
    uint16_t ocr1b;
} volatile timer1_t;

volatile timer1_t *timer1 = (timer1_t *)(0x80);

// registro mascara de interrupciones timer 1
volatile uint8_t *timer1_timsk = (uint8_t *)(0x6F);

void timer1_init()
{
    // modo de comparacion para Fast PWM.
    timer1->tccr1a |= (1 << 7) | (1 << 5);
    // modo Fast PWM con top en icr1 (el modo 14) 1110. 
    timer1->tccr1a |= (1 << 1);
    timer1->tccr1b |= (1 << 4) | (1 << 3);
    // preescalar 8 sería CS2:CS1:CS0, 010
    /*con el preescalar 8 hace 10000 ticks en 20 ms, 500 en 1ms y 1000 en 2ms*/
    timer1->tccr1b |= (1 << 1);
    // ICR1 seteamos el tope para que sea en los 20ms
    timer1->icr1 = 9900; 
    // hacemos el puerto D9 de salida (el predilecto para ocr1a)
    *DDR_B |= (1 << 1);
    *DDR_B |= (1 << 2);

}

void timer1_rotacion_servo(int num){
    //usamos ocr1a = D9. Conectar el servo al PIN D9
    timer1->ocr1a = num;
}

void timer1_motor(volatile int val) {
    //usamos ocr1b = D10. Conectar el motor al PIN D10
    volatile int tope = 0;
    if(val == 100) {
        tope = timer1->icr1;
    } else if (val != 0) {
        tope = timer1->icr1 / 100;
        tope = val * tope;
    }
    timer1->ocr1b = tope;
}

