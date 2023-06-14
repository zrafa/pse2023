#include <avr/interrupt.h>
#include <avr/io.h>

typedef struct {     // Timer/Contador 1
    uint8_t tccr1a;  // Registro de Control A
    uint8_t tccr1b;  // Registro de Control B
    uint8_t tccr1c;  // Registro de Control C
    uint8_t reserved;
    uint8_t tcnt1l;  // Registro Timer/Contador Byte Bajo
    uint8_t tcnt1h;  // Registro Timer/Contador Byte Alto
    uint8_t icr1l;   // Input Capture Register Low Byte
    uint8_t icr1h;   // Input Capture Register High Byte
    uint8_t ocr1al;  // Registro Comparador A Byte Bajo
    uint8_t ocr1ah;  // Registro Comparador A Byte Alto
    uint8_t ocr1bl;  // Registro Comparador B Byte Bajo
    uint8_t ocr1bh;  // Registro Comparador B Byte Alto
} volatile timer1_t;

// registro mascara de interrupciones timer 1
volatile unsigned char* timer1_timsk1 = (unsigned char*)(0x6F);

volatile timer1_t* timer1 = (timer1_t*)(0x80);

// Prescalar 8, Fast PWM, tope ICR1, OC1A = 0 al matchear OCR1A
#define TIMER1_FPWM1 0b10000010  // COM1A1|COM1A0|-|-|-|-|WGM11|WGM10
#define TIMER1_FPWM2 0b11010     // WGM13|WGM12|CS12|CS11|CS10

#define f_CLK 4000000U
#define TIMER1_PRESCALAR 8U
#define f_PWM 50U  // 50 ticks = 1000 ms

// Duración del periodo: TOP = ICR1 = (f_CLK / (TIMER2_PRESCALAR * f_PWM) ) - 1
#define TIMER1_ICR1 ((f_CLK / (TIMER1_PRESCALAR * f_PWM)) - 1)
#define TIMER1_ICR1H ((uint8_t)(TIMER1_ICR1 >> 8))
#define TIMER1_ICR1L ((uint8_t)TIMER1_ICR1)

// Duración mínima del pulso (servo a 0 grados): OCR1A = TIMER1_ICR1 / 40
#define TIMER1_OCR1A ((uint16_t)(TIMER1_ICR1 / 40))
#define TIMER1_OCR1AH ((uint8_t)(TIMER1_OCR1A >> 8))
#define TIMER1_OCR1AL ((uint8_t)(TIMER1_OCR1A))

// Duración máxima del pulso (servo a 180 grados): OCR1A = TIMER1_ICR1 / 10
#define SERVO_MAX ((uint16_t)(TIMER1_ICR1 / 10))
#define SERVO_MAXH ((uint8_t)(SERVO_MAX >> 8))
#define SERVO_MAXL ((uint8_t)(SERVO_MAX))

// Calcular cuanto hay que cambiar el pulso por cada grado
#define GRADO ((SERVO_MAX - TIMER1_OCR1A) / 180)

void timer1_init() {
    timer1->tccr1a |= TIMER1_FPWM1;
    timer1->tccr1b |= TIMER1_FPWM2;
    timer1->icr1h = TIMER1_ICR1H;
    timer1->icr1l = TIMER1_ICR1L;
    timer1->ocr1ah = TIMER1_OCR1AH;
    timer1->ocr1al = TIMER1_OCR1AL;
}

void timer1_fijar_angulo(unsigned int angulo) {
    unsigned long temp;
    // Servo puede ir de 0 a 180 grados
    if (angulo > 0 && angulo < 180)
        temp = TIMER1_OCR1A + (angulo * GRADO);
    else if (angulo <= 0)
        temp = TIMER1_OCR1A;
    else
        temp = SERVO_MAX;
    timer1->ocr1ah = (uint8_t)(temp >> 8);
    timer1->ocr1al = (uint8_t)temp;
}
