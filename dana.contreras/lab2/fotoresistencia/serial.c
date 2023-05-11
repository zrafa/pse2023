
/**********************************************************************
 *
 * serial.c - Driver del UART del atmega328p
 *
 * META : ocultar el hardware a la aplicacion 
 *
 * Configuracion: 2400bps, 8bits data, 1bit stop, sin bit de paridad
 *
 **********************************************************************/

#include <stdint.h> /* para los tipos de datos. Ej.: uint8_t */

typedef struct
{
    uint8_t status_control_a; /* ucsr0a USART Control and Status A */
    uint8_t status_control_b; /* ucsr0b USART Control and Status B */
    uint8_t status_control_c; /* ucsr0c USART Control and Status C */
    uint8_t _reserved; /* espacio sin utilizar */
    uint8_t baud_rate_l; /* ubrr0l baud rate low */
    uint8_t baud_rate_h; /* ubrr0h baud rate high */
    uint8_t data_es; /* udr0 i/o data */

} volatile uart_t;

/* puntero a la estructura de los registros del periferico */
volatile uart_t *serial_port = (uart_t *) (0xc0);

#define F_CPU 4000000UL
#define USART_BAUDRATE 2400
#define BAUD_PRESCALE (((F_CPU/(USART_BAUDRATE*16UL)))-1)
#define RECEIVER_ENABLE 0x10 /* RXEN0 Habilitar la recepcion */
#define TRANSMITTER_ENABLE 0x08 /* TXEN0 Habilitar la transmicion */
#define READY_TO_READ 0x80 /* RXC0 Dato listo para leer */
#define READY_TO_WRITE 0x20 /* UDRE0 Buffer vacio listo para escribir */
#define INIT 0x06 /* frame 8-n-1 */
#define EN_RX_TX ((RECEIVER_ENABLE)|(TRANSMITTER_ENABLE))

void serial_init()
{
	/* Configuracion de los registros High y Low con BAUD_PRESCALE */
	serial_port->baud_rate_h = (unsigned char) (BAUD_PRESCALE>>8);
    serial_port->baud_rate_l = (unsigned char) (BAUD_PRESCALE);
    
    /* Configuracion de un frame de 8bits, sin bit de paridad y bit de stop */
	serial_port->status_control_c = (unsigned char) (INIT);
    
    /* Activacion de la recepcion y transmicion */
    serial_port->status_control_b = (unsigned char) (EN_RX_TX);
}

/* enviar un byte a traves del dispositivo inicializado */
void serial_put_char(char c)
{

    /* completar con E/S programada */
    /* Se debe esperar verificando el bit UDREn del registro UCSRnA,
       hasta que el buffer esté listo para recibir un dato a transmitir */

    while(!((serial_port->status_control_a) & (READY_TO_WRITE)));

    serial_port->data_es = c;

}

void serial_put_str(char * string)
{
    while(*string) {
        serial_put_char(*string);
        string++;
    }
}

char serial_get_char_ready(void)
{
    return (serial_port->status_control_a>>7);
}

int serial_get_char(void)
{
     /* Wait for the next character to arrive. */
    
    while (!((serial_port->status_control_a)>>7));

    return (serial_port->data_es);

}

