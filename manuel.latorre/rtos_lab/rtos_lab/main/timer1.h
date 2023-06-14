/**********************************************************************
 *
 * Filename:    timer1.h
 *
 * API para la aplicacion embebida
 * META : ocultar el hardware a la aplicacion
 *
 **********************************************************************/
#ifndef _TIMER1_H
#define _TIMER1_H

int timer1_init();
int timer1_pwm_move_to(int grade);
int timer1_motor(int speed);
#endif /* _TIMER1_H */