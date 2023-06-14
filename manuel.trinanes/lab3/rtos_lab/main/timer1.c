#include <xinu.h>

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
volatile uint8_t *timer1_timsk = (uint8_t *)(0x6F);

// Bits for Compare Output Mode
#define COM1A1 7
#define COM1B1 5

// Bits for Waveform Generation Mode
#define WGM10 0
#define WGM11 1
#define WGM12 3
#define WGM13 4

// Bits for Prescaler
#define CS10 0
#define CS11 1
#define CS12 2

volatile unsigned char* DDR_B = (unsigned char*) 0x24;

void init_timer1()
{
    // D9 and D10 as PWM output (OC1A and OC1B)
    *DDR_B |= (1 << 1);
    *DDR_B |= (1 << 2);

    // Clear OC1A1 on Compare Match (set output low level)
    timer1->tccr1a |= (1 << COM1A1) | (1 << COM1B1);
    // Fast PWM with top ICR1
    timer1->tccr1a |= (1 << WGM11);
    timer1->tccr1b |= (1 << WGM13) | (1 << WGM12);
    // 8 prescaler (0.5 tick per us)
    timer1->tccr1b |= (1 << CS11);
    // ICR1 (when the counter register must be cleared, or length in ticks of the period)
    timer1->icr1 = 9900; // 20ms = 50hz -> 4MHz / (8 * 10000) = 50Hz

    sleepms(500);
}

set_timer1_ocr1a(int val) {
    timer1->ocr1a = val;
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