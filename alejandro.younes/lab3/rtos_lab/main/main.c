#include <avr/interrupt.h>
#include <xinu.h>
#include "adc.h"
#include "serial.h"
#include "timer.h"
#include "utils.h"

#define LEDL 0b00100000  // PB5 = LEDL = D13 (Nano)
#define OC1A 0b00000010  // PB1 = OC1A =  D9 (Nano)
#define OC2B 0b00001000  // PD3 = OC2B =  D3 (Nano)

// definicion de tareas (cuyo codigo fuente es externo)
extern int tarea_motor();
extern int tarea_reporte();
extern int tarea_control();
extern int tarea_servo();

// semaforos
#define SEM_MOTOR 0
#define SEM_SERVO 1

// variables globales
unsigned int timer1_demora_led = 100;
unsigned int timer1_ticks = 0;
unsigned int timer1_angulo = 0;
unsigned int timer1_segundo = 0;
unsigned int timer1_minuto = 0;
unsigned int timer1_hora = 0;
unsigned int timer2_velocidad_motor = 0;

ISR(TIMER1_OVF_vect) {
    if (timer1_ticks % timer1_demora_led == 0)  // parpadear LED
        portb_cambiar_pin(LEDL);
    timer1_ticks++;
    if (timer1_ticks % 50 == 0) {  // contar un segundo
        timer1_segundo++;
        if (timer1_segundo == 60) {  // contar un minuto
            timer1_segundo = 0;
            timer1_minuto++;
            if (timer1_minuto == 60) {  // contar una hora
                timer1_minuto = 0;
                timer1_hora++;
            }
        }
    }
    if (timer1_ticks == 255)  // si se llega al limite de los 8 bits
        timer1_ticks = 0;     // reinicializar para evitar overflow
}

// main es una tarea independiente y se la utiliza como tal
int main(void) {  // prioridad 20, pila 256 bytes
    unsigned int vel_ant = 0;
    unsigned int vel_act;
    // inicializar perifericos
    serial_init();
    adc_init();
    portb_init();
    portb_como_salida_pin(OC1A);
    portb_como_salida_pin(LEDL);
    portb_subir_pin(LEDL);
    portd_init();
    portd_como_salida_pin(OC2B);
    timer1_init();
    timer2_init();
    sei();
    // crear tareas
    resume(create(tarea_servo, 64, 50, "servo", 0));
    resume(create(tarea_control, 64, 40, "control", 0));
    resume(create(tarea_motor, 64, 30, "motor", 0));
    resume(create(tarea_reporte, 256, 10, "reporte", 0));
    // medir valor del knob para cambiar velocidad del motor y LED
    while (1) {
        sleepms(101);
        vel_act = adc_get_0() / 40.9;  // 4096/40.9 = 100
        if (vel_act != vel_ant) {
            timer2_velocidad_motor = vel_act;
            sync_signal(SEM_MOTOR);
            vel_ant = vel_act;
        }
        timer1_demora_led = 1000 / (vel_act + 10);
    }
}
