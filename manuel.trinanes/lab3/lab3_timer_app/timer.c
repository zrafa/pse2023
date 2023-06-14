#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

typedef struct {
    uint8_t tccr0a;
    uint8_t tccr0b;
    uint8_t tccr0;
    uint8_t ocr0a;
    uint8_t ocr0b;
} volatile timer0_t;
volatile timer0_t *timer0 = (timer0_t *)(0x44);
volatile unsigned char *timer0_timsk0 = (unsigned char *)(0x6E);

#define TIMER0_CS 0b011 // clock / 64
#define TIMER0_CTC 0b010 // WGM01 = 1 and WGM00 = 0, means CTC
#define SYSTEM_TICKS 4000000UL
#define PRESCALAR 64
#define TICKS_PER_SECOND 1000
#define TIMER0_OCR0A (SYSTEM_TICKS/PRESCALAR/TICKS_PER_SECOND)
volatile int delay_ms;
volatile int ticks = 0;
volatile char timer0_flag = 0;

void timer0_init(void) {
    timer0->tccr0a |= TIMER0_CTC;
    timer0->tccr0b |= TIMER0_CS;
    timer0->ocr0a |= TIMER0_OCR0A;
    (*timer0_timsk0) |= 0b10;
}

// Setter
void timer0_set_ms(int ms) {
    delay_ms = ms;
}

// Restart
void timer0_restart() {
    ticks = 0;
    timer0_flag = 0;
}

// Read timer
char timer0_read() {
    char local_flag = 0;
    cli();
    if(timer0_flag == 1) {
        local_flag = timer0_flag;
        timer0_flag = 0;
    }
    sei();
    return local_flag;
}

// Wait
void timer0_wait(int ms) {
    delay_ms = ms;
    ticks = 0;
    timer0_flag = 0;
    while(!timer0_read());
}

// Interruption routine
ISR(TIMER0_COMPA_vect) {
    ticks++;
    if(ticks == delay_ms) {
        ticks = 0;
        timer0_flag = 1;
    }
}