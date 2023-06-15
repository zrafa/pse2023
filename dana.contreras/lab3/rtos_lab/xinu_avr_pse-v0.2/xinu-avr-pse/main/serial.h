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
char serial_get_char_ready(void);
void serial_put_str(char *);
void serial_put_int(int value, int num_digits);

#endif /* _SERIAL_H */
