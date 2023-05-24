#include <avr/interrupt.h>

typedef struct
{
    uint8_t tccr1a; /* Register control A timer 1 */
    uint8_t tccr1b; /* Register control B of timer 1 */
    uint8_t tccr1c;
    uint8_t reserved;
    uint8_t tcnt1l;
    uint8_t tcnt1h;
    uint8_t icr1l;
    uint8_t icr1h;
    uint8_t ocr1al;  /* Register compare A */
    uint8_t ocr1ah;
    uint8_t ocr1bl;  /* Register compare B */
    uint8_t ocr1bh;

} timer1_t;

volatile timer1_t *timer1 = (timer1_t *) (0x80);
volatile unsigned char *timer1_timsk1 = (unsigned char *)(0x6F);
volatile unsigned char * DDR_B  = (unsigned char *) 0x24;

volatile uint16_t TOP;

#define WGM11 1
#define WGM12 3
#define WGM13 4
#define CS10 0
#define COM1A1 7
#define COM1B1 5

void timer1_init()
{

    // fast pwm mode
    timer1->tccr1a |= (1<<WGM11);
    timer1->tccr1b |= ((1<<WGM13) | (1<<WGM12));

    // no prescaling
    timer1->tccr1b |= (1<<CS10);

    // top: 500
    timer1->icr1h = 0x01;
    timer1->icr1l = 0xF4;

    // pin 9: output
    *DDR_B |= 0x02; 

    // clear OC1A/OC1B on Compare Match, set OC1A/OC1B at BOTTOM (non-inverting mode)
    timer1->tccr1a |= ((1<<COM1A1) | (1<<COM1B1));

    // overflow interrupt enable
    *timer1_timsk1 |= 0x01;

}

void setOCRnA(uint16_t value)
{
    TOP = value;
}

ISR(TIMER1_OVF_vect)
{
    timer1->ocr1ah = (TOP>>8);
    timer1->ocr1al = TOP;
}