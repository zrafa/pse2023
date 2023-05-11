
/**********************************************************************
 *
 * serial.c - Driver del UART del atmega328p
 *
 * META : ocultar el hardware a la aplicacion
 *
 * Configuracion: 9600bps, 8bits data, 1bit stop, sin bit de paridad
 *
 **********************************************************************/

#include <stdint.h> // para los tipos de datos, p.e.: uint8_t
#include <stdio.h>

// Estructura de datos del driver UART (serial)
typedef struct {
    uint8_t status_control_a;  // UCSR0A USART Control and Status Register 0 A
    uint8_t status_control_b;  // UCSR0B USART Control and Status Register 0 B
    uint8_t status_control_c;  // UCSR0C USART Control and Status Register 0 C
    uint8_t reserved1;
    uint8_t baud_rate_low;   // UBRR0L USART Baud Rate Register Low
    uint8_t baud_rate_high;  // UBRR0H USART Baud Rate Register High
    uint8_t data_es;         // UDR0   USART I/O Data Register
} volatile uart_t;

// puntero a la estructura de los registros del periferico
uart_t* puerto_serial = (uart_t*)(0xc0);

#define F_CPU 4000000UL
#define USART_BAUDRATE 2400
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

// Registro status_control_n_a
#define UDREn 0b00100000
#define RXCn 0b10000000
// Registro status_control_n_b
#define UCSZn2 0b00000100
#define TXENn 0b00001000
#define RXENn 0b00010000
// Registro status_control_n_c
#define UCSZn0 0b00000001
#define UCSZn1 0b00000010
#define USBSn 0b00001000
#define UPMn0 0b00010000
#define UPMn1 0b00100000

void serial_init() {
    // Configurar los registros High y Low con BAUD_PRESCALE
    puerto_serial->baud_rate_high = (unsigned char)(BAUD_PRESCALE >> 8);
    puerto_serial->baud_rate_low = (unsigned char)BAUD_PRESCALE;
    // Configurar frame de 8 bits
    puerto_serial->status_control_c = puerto_serial->status_control_c | UCSZn0;
    puerto_serial->status_control_c = puerto_serial->status_control_c | UCSZn1;
    puerto_serial->status_control_b = puerto_serial->status_control_b & ~UCSZn2;
    // Configurar sin bit de paridad
    puerto_serial->status_control_c = puerto_serial->status_control_c & ~UPMn0;
    puerto_serial->status_control_c = puerto_serial->status_control_c & ~UPMn1;
    // Configurar 1 bit de stop
    puerto_serial->status_control_c = puerto_serial->status_control_c & ~USBSn;
    // Activar recepción y transmisión
    puerto_serial->status_control_b = puerto_serial->status_control_b | RXENn;
    puerto_serial->status_control_b = puerto_serial->status_control_b | TXENn;
}

// enviar un byte a traves del dispositivo inicializado
void serial_put_char(char c) {
    // esperar hasta que el bit UDREn del registro UCSRnA sea 1
    // entonces buffer está listo para recibir dato a transmitir
    while ((puerto_serial->status_control_a & UDREn) == 0) {
    }

    // enviar char c por el puerto serie
    puerto_serial->data_es = c;
}

// esperar un byte a traves del dispositivo inicializado
char serial_get_char(void) {
    // Completar con E/S programada similar a serial_put_char pero utilizando el
    // bit correcto
    while ((puerto_serial->status_control_a & RXCn) == 0) {
    }

    // devolver valor que se encuentra en el registro de datos de E/S
    return puerto_serial->data_es;
}

int serial_get_char_ready(void) {
    return puerto_serial->status_control_a & RXCn;
}

void serial_put_int(int num) {
    int digitos = 5;
    char buffer[digitos];
    snprintf(buffer, digitos, "%04d", num);
    for (int i = 0; i < digitos; i++)
        serial_put_char(buffer[i]);
}
