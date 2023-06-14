#ifndef _UTILS_H
#define _UTILS_H

void portb_init();
void portb_como_salida_pin(unsigned char numero);
void portb_como_entrada_pin(unsigned char numero);
void portb_subir_pin(unsigned char numero);
void portb_bajar_pin(unsigned char numero);
void portb_cambiar_pin(unsigned char numero);
unsigned int portb_leer_pin(unsigned char numero);

void portd_init();
void portd_como_salida_pin(unsigned char numero);
void portd_como_entrada_pin(unsigned char numero);
void portd_subir_pin(unsigned char numero);
void portd_bajar_pin(unsigned char numero);
void portd_cambiar_pin(unsigned char numero);
unsigned int portd_leer_pin(unsigned char numero);

#endif
