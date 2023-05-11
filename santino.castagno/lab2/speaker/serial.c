
/**********************************************************************
 *
 * serial.c - Driver del UART del atmega328p
 *
 * META : ocultar el hardware a la aplicacion
 *
 * Configuracion: 9600bps, 8bits data, 1bit stop, sin bit de paridad
 *
 **********************************************************************/

#include "serial.h"
#include <stdint.h>

typedef struct
{
    uint8_t status_control_a; // ucsr0a USART Control and Status A
    uint8_t status_control_b; // ucsr0b USART Control and Status B
    uint8_t status_control_c; // ucsr0c USART Control and Status A
    uint8_t _reserved;        // espacio sin utilizar
    uint8_t baud_rate_l;      // ubrr0l baud rate low
    uint8_t baud_rate_h;      // ubrr0h baud rate high
    uint8_t data_es;          // udr0 i/o data

} volatile uart_t;

uart_t *puerto_serial = (uart_t *)(0xc0); // puntero a la estructura de los registros del periferico

#define USART_BAUDRATE 9600
#define F_CPU 16000000 // 16MHZ es la frecuencia del microcontrolador en el arduino uno
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)
#define INIT 0b00000110 // USART asincrono; modo de paridad deshabilitado; un bit de stop; 8-bit de tamanio de frame

// mascaras de bits para usos comunes
#define RECEIVER_ENABLE 0x10    // RXEN0 Habilitar la recepcion
#define TRANSMITTER_ENABLE 0x08 // TXEN0 Habilitar la transmision
#define CHARACTER_SIZE_0 0x20   // UCSZ00 Numero de bits del dato de e/s
#define CHARACTER_SIZE_1 0x40   // UCSZ01 Numero de bits del dato de e/s
#define READY_TO_READ 0x80      // RXC0 Dato listo para leer
#define READY_TO_WRITE 0x20     // UDRE0 Buffer vacio listo para escribir

void serial_init() // Rutina de inicializacion
{
    /* Configurar un frame de 8bits, sin bit de paridad y bit de stop */
    puerto_serial->status_control_c = (unsigned char)(INIT);

    /* Activar la recepcion y transmision */
    puerto_serial->status_control_b = (unsigned char)(RECEIVER_ENABLE | TRANSMITTER_ENABLE);

    /* Configurar los registros High y Low */
    puerto_serial->baud_rate_h = (unsigned char)(BAUD_PRESCALE >> 8);
    puerto_serial->baud_rate_l = (unsigned char)(BAUD_PRESCALE);
}

void serial_put_char(char c)
{
    while (!((puerto_serial->status_control_a) & (READY_TO_WRITE)))
        ;
    puerto_serial->data_es = (unsigned char)c;
}

void serial_put_string(char *str)
{
    char tmp, i = 0;
    do
    {
        tmp = *(str + i);
        serial_put_char(tmp);
        i++;
    } while (tmp != '\0');
}

void serial_put_int(int val, int digitos)
{
    int tmp, i = digitos;
    char num[digitos];

    while (i > 0)
    {
        tmp = val % 10;
        val = val / 10;
        num[i - 1] = tmp + 48;
        i--;
    }

    for (i = 0; i < digitos; i++)
    {
        serial_put_char(num[i]);
    }
}

int serial_get_char_ready(void)
{
    return ((puerto_serial->status_control_a) & (READY_TO_READ)) != 0;
}

char serial_get_char(void)
{
    while (((puerto_serial->status_control_a) & (READY_TO_READ)) == 0)
        ;
    return (puerto_serial->data_es);
}
