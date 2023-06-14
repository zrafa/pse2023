#ifndef _TIMER_H
#define _TIMER_H

void timer0_init(void);
void timer0_set_ms(int ms);
void timer0_restart(void);
char timer0_read(void);
void timer0_wait(int ms);
extern volatile char timer0_flag;

#endif /* _TIMER_H */
