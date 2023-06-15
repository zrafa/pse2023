/**********************************************************************
 *
 * timer1.c - Driver del TIMER 1 (16 bits) del atmega328p
 *
 * META : ocultar el hardware a la aplicacion
 *
 **********************************************************************/

#include <stdint.h>
#include <avr/interrupt.h>
#include "timer1.h"
#include "serial.h"

/* Macros para la configuracion de los registros de control */
#define CONF_CONTROL_REG_A_FPWM 0b10100010; // [COM1A1|COM1A2] clear on match - [COM1B1|COM1B2] clear on match -[WGM11|WGM10] fast PWM
#define CONF_CONTROL_REG_B_FPWM 0b00011010; // [WGM13|WGM12] fast PWM         - [CS02|CS01|CS00] preescale 8
#define CONF_CONTROL_REG_C_FPWM 0b00000000; //

/********************** CALCULOS DE VALORES ***************************
 * FREQCPUUNO:  16000000
 * PREESCALAR:         8
 * f_cpu/prescalar = 16000000/8 = 2000000 t/s
 *
 * FREQ:  2000000 t/s * 0.020         = 40000 = 0x9c40
 *
 * MIN-STD:   2000000 t/s * 0.001     =  2000 = 0x07d0
 * MAX-STD:   2000000 t/s * 0.002     =  4000 = 0x0fa0
 * MIN-SERVO: 2000000 t/s * 0.0005            = 0x03e8
 * MAX-SERVO  2000000 t/s * 0.0022            = 0x1130
 *
 * MAX-MOTOR = FREQ = 0x9c40
 **********************************************************************/

/* Macros de valores */
#define NMIN_PWM_8P 0x03e8
#define NMAX_PWM_8P 0x1130
#define TIMER1_FREQ_H 0x9c
#define TIMER1_FREQ_L 0x40
#define TIMER1_0CR1AH_POS 0x03
#define TIMER1_0CR1AL_POS 0xe8
#define TIMER1_0CR1BH_POS 0x00
#define TIMER1_0CR1BL_POS 0x00
#define MAX_MOTOR 0x9c40

/* Estructura de datos del driver TIMER */
typedef struct
{
        uint8_t control_reg_a;      // TCC1RA
        uint8_t control_reg_b;      // TCC1RB
        uint8_t control_reg_c;      // TCC1RC
        uint8_t _reserved;          //
        uint8_t counter_reg_l;      // TCNT1L
        uint8_t counter_reg_h;      // TCNT1H
        uint8_t in_capture_regl;    // ICR1L
        uint8_t in_capture_regh;    // ICR1H
        uint8_t out_compare_reg_al; // OCR1AL
        uint8_t out_compare_reg_ah; // OCR1AH
        uint8_t out_compare_reg_bl; // OCR1BL
        uint8_t out_compare_reg_bh; // OCR1BH
} volatile timer1_t;
volatile timer1_t *timer = (timer1_t *)0x80; // Direccion base

volatile uint8_t *timer_interrupt_mask_reg = (uint8_t *)0x6f; // TIMSK
volatile uint8_t *timer_interrupt_flag_reg = (uint8_t *)0x36; // TIFR1 (no se si sirve de algo)

volatile int ticks;

int timer1_init()
{
        /* setear la configuracion del timer1  */
        timer->control_reg_a |= CONF_CONTROL_REG_A_FPWM;
        timer->control_reg_b |= CONF_CONTROL_REG_B_FPWM;
        timer->control_reg_c |= CONF_CONTROL_REG_C_FPWM;

        /* determinar la frecuencia con el registro ICR  */
        timer->in_capture_regh = TIMER1_FREQ_H;
        timer->in_capture_regl = TIMER1_FREQ_L;

        /* determinamos el ancho de la senial en alto en cada ciclo para el PIN0C1A con el registro OCR1A (pinout para el servo) */
        timer->out_compare_reg_ah = TIMER1_0CR1AH_POS;
        timer->out_compare_reg_al = TIMER1_0CR1AL_POS;

        /* determinamos el ancho de la senial en alto en cada ciclo para el PIN0C1B con el registro OCR1A (pinout para el motor) */
        timer->out_compare_reg_bh = 0x00;
        timer->out_compare_reg_bl = 0x00;

        /* reiniciamos los registros del contador */
        timer->counter_reg_l = 0;
        timer->counter_reg_h = 0;
        return 0;
}

/**
 * POS: posicion del servo (min 0 y max 100)
 */
int timer1a_pwm_move_to(int pos)
{
        long int init_value, temp;
        uint8_t low, high;

        if (pos < 0 || pos > 100)
                return 1;

        temp = NMIN_PWM_8P + (NMAX_PWM_8P - NMIN_PWM_8P) / 100 * pos;
        high = (temp >> 8);
        low = temp;

        /* determinamos el ancho de la senial en alto en cada ciclo con el registro OCR1A */
        timer->out_compare_reg_ah = high;
        timer->out_compare_reg_al = low;

        return 0;
}

/*
 * MAX-STD: 2000000 t/s * 0.002     =  4000 = 0x0fa0
 * MAX-SERVO 2000000 t/s * 0.0022            = 0x1130
 */
int timer1a_pwm_max()
{
        // timer->out_compare_reg_ah = 0x0f;
        // timer->out_compare_reg_al = 0x9f;
        timer->out_compare_reg_ah = 0x11;
        timer->out_compare_reg_al = 0x30;
}

/*
 * MIN-STD:   2000000 t/s * 0.001    =  2000 = 0x07d0
 * MIN-SERVO:  2000000 t/s * 0.0005           = 0x03e8
 */

int timer1a_pwm_min()
{

        timer->out_compare_reg_ah = 0x10;
        timer->out_compare_reg_al = 0x68;
}

/**
 * SPEED: velocidad del motor (min 0 y max 100)
 */
int timer1b_pwm_move_to(int speed)
{
        long int init_value, temp;
        uint8_t low, high;

        if (speed < 0 || speed > 100)
                return 1;

        temp = MAX_MOTOR / 100 * speed;
        high = (temp >> 8);
        low = temp;

        /* determinamos el ancho de la senial en alto en cada ciclo con el registro OCR1B */
        timer->out_compare_reg_bh = high;
        timer->out_compare_reg_bl = low;

        return 0;
}
