
#include <avr/interrupt.h>
#include <avr/io.h>

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

volatile unsigned char* DDR_B = (unsigned char*) 0x24;

void timer1_init()
{
    // hacemos el puerto D9 de salida (el predilecto para ocr1a)
    *DDR_B |= (1 << 1);
    // modo de comparacion para Fast PWM.
    timer1->tccr1a |= (1 << 7) | (1 << 5);
    // modo Fast PWM con top en icr1 (el modo 14) 1110. 
    timer1->tccr1a |= (1 << 1);
    timer1->tccr1b |= (1 << 4) | (1 << 3);
    // preescalar 8 sería CS2:CS1:CS0, 010
    /*con el preescalar 8 hace 10000 ticks en 20 ms, 500 en 1ms y 1000 en 2ms*/
    timer1->tccr1b |= (1 << 1);
    // ICR1 seteamos el tope para que sea en los 20ms
    timer1->icr1 = 10000; 

}

void timer1_rotacion_servo(int num){
    timer1->ocr1a = num;
}

set_timer1_ocr1b_dutycycle(int val) {
    int duty_cycle = 0;
    if(val == 100) {
        duty_cycle = timer1->icr1;
    } else if (val != 0) {
        duty_cycle = timer1->icr1 / 100;
        duty_cycle = val * duty_cycle;
    } else if (val < 2) {
        duty_cycle = 0;
    }
    timer1->ocr1b = duty_cycle;
}