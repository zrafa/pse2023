
#include <avr/io.h>
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

} volatile timer1_t;

volatile timer1_t *timer1 = (timer1_t *) (0x80);

void timer1_init()
{

    // fast pwm mode
    timer1->tccr1a |= (1<<WGM11);
    timer1->tccr1b |= ((1<<WGM13) | (1<<WGM12));

    // no prescaling
    timer1->tccr1b |= (1<<CS10);

    /* top: 500
    timer1->icr1h = 0x01;
    timer1->icr1l = 0xF4;
    */
    // top: 512
    timer1->icr1h = 0x02;
    timer1->icr1l = 0x00;

    // pin 9: output
    DDRB |= (1 << PB1); 

}

void setOCRnA(uint16_t value)
{
    timer1->ocr1ah = (value>>8);
    timer1->ocr1al = (uint8_t)((value << 8) >> 8);
}