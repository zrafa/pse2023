/**********************************************************************
 *
 * Filename:    serial.h
 * 
 * API para la aplicacion embebida 
 * META : ocultar el hardware a la aplicacion 
 *
 **********************************************************************/

#ifndef _SERIAL_H
#define _SERIAL_H

void serial_init(void);
void serial_put_char(char);
char serial_get_char(void);
int serial_get_char_ready();
char serial_get_char_interrupt(void);
void serial_put_str(char *);

#endif
