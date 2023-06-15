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
int timer1a_pwm_move_to(int pos);
int timer1a_pwm_max();
int timer1a_pwm_min();
int timer1b_pwm_move_to(int speed);

#endif /* _TIMER1_H */