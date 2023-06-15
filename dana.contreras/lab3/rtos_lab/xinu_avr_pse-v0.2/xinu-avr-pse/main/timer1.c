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
volatile unsigned char * DDR_B  = (unsigned char *) 0x24;

#define WGM11 1
#define WGM12 3
#define WGM13 4
#define CS11 1
#define COM1A1 7
#define COM1B1 5

#define MIN_SERVO 500
#define MIN_MOTOR 0 
#define MAX 1000
#define TOP 10000

void timer1_init()
{
    // fast pwm mode
    timer1->tccr1a |= (1<<WGM11);
    timer1->tccr1b |= ((1<<WGM13) | (1<<WGM12));

    // prescaler 8
    timer1->tccr1b |= (1<<CS11);

    // compare output mode: clear OC1A/OC1B on Compare Match, set OC1A/OC1B at BOTTOM (non-inverting mode)
    timer1->tccr1a |= (1<<COM1A1);
    timer1->tccr1a |= (1<<COM1B1);

    // top: 10000
    timer1->icr1h = (TOP & 0xFF00) >> 8;
    timer1->icr1l = (TOP & 0x00FF);

    // min for servo: 500
    timer1->ocr1ah = (MIN_SERVO & 0xFF00) >> 8;
    timer1->ocr1al = (MIN_SERVO & 0x00FF);

    // min for motor: 0
    timer1->ocr1bh = (MIN_MOTOR & 0xFF00) >> 8;
    timer1->ocr1bl = (MIN_MOTOR & 0x00FF);

    // pin 9: output for servo
    (*DDR_B) |= 0x02; 

    // pin 10: output for motor cc
    (*DDR_B) |= 0x04;

}

void set_OCR1A(uint16_t new_value)
{
    timer1->ocr1ah = (new_value>>8);
    timer1->ocr1al = new_value;
}

void set_OCR1B(uint16_t value)
{
    timer1->ocr1bh = (value>>8);
    timer1->ocr1bl = value;
}
