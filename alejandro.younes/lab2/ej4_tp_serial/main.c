/**********************************************************************
 *
 * main.c - TP2 E4
 *
 **********************************************************************/

#include "serial.h"
#include "utils.h"

// pines ultrasonido
#define ECHO 0b00000001  // D8 (Nano) = PB0 conectado a pin ECHO de HC-SR04
#define TRIG 0b00000010  // D9 (Nano) = PB1 conectado a pin TRIG de HC-SR04

// pines knight rider
#define LED_1 0b00000100  // D10 (Nano) = PB2 conectado a ánodo 1er LED
#define LED_2 0b00001000  // D11 (Nano) = PB3 conectado a ánodo 2do LED
#define LED_3 0b00010000  // D12 (Nano) = PB4 conectado a ánodo 3er LED

volatile unsigned long i;
volatile char caracter_recibido = '?';

unsigned int espera_knight_rider() {
  for (i = 0; i < 100000; i++) {
    if (serial_get_char_ready())
      caracter_recibido = serial_get_char();
  }
  if (caracter_recibido == 'k') {
    bajar_pin_port_b(LED_1);
    bajar_pin_port_b(LED_2);
    bajar_pin_port_b(LED_3);
    return 1;
  }

  return 0;
}

void knight_rider(void) {
  inicializar_port_b();
  salida_pin_port_b(LED_1);
  salida_pin_port_b(LED_2);
  salida_pin_port_b(LED_3);

  while (1) {
    levantar_pin_port_b(LED_1);
    if (espera_knight_rider())
      break;
    bajar_pin_port_b(LED_1);
    levantar_pin_port_b(LED_2);
    if (espera_knight_rider())
      break;
    bajar_pin_port_b(LED_2);
    levantar_pin_port_b(LED_3);
    if (espera_knight_rider())
      break;
    bajar_pin_port_b(LED_3);
    levantar_pin_port_b(LED_2);
    if (espera_knight_rider())
      break;
    bajar_pin_port_b(LED_2);
  }
}

void mostrar_medida(int valor) {
  serial_put_int(valor);
  serial_put_char(' ');
  serial_put_char('c');
  serial_put_char('m');
  serial_put_char('\r');
  serial_put_char('\n');
}

void ultrasonido() {
  unsigned long t;
  unsigned long tiempo_us;
  unsigned int distancia_cm;

  inicializar_port_b();
  entrada_pin_port_b(ECHO);
  salida_pin_port_b(TRIG);

  t = 0;
  levantar_pin_port_b(TRIG);            // levantar trigger
  delay_10us();                         // esperar que tome solicitud
  bajar_pin_port_b(TRIG);               // bajar trigger
  while (leer_pin_port_b(ECHO) != 1) {  // esperar que echo levante
  }
  while (leer_pin_port_b(ECHO) == 1) {  // contar duración echo
    t++;
    delay_10us();
  }
  tiempo_us = t * 10;
  distancia_cm = tiempo_us / 58;
  mostrar_medida(distancia_cm);
  delay_ms(500);  // esperar para solicitar nueva medición
}

int main(void) {
  serial_init();

  serial_put_char('i');
  serial_put_char('n');
  serial_put_char('i');
  serial_put_char('c');
  serial_put_char('i');
  serial_put_char('o');
  serial_put_char('\r');
  serial_put_char('\n');

  while (1) {
    if (serial_get_char_ready()) {
      caracter_recibido = serial_get_char();
      if (caracter_recibido == 'k') {
        caracter_recibido = '?';
        knight_rider();
      } else if (caracter_recibido == 'u') {
        caracter_recibido = '?';
        ultrasonido();
      }
    }
  }
}
