#include <xinu.h>

#include <avr/interrupt.h>

// #define F_CPU 4000000UL
#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU/(USART_BAUDRATE*16UL)))-1)
#define INIT 0x06
#define EN_RX_TX 0x18
#define UART_RXCIE0 7 
#define EN_TX 0x20
#define EN_RX 0x80

typedef struct {
	uint8_t status_control_a;    /* ucsr0a USART Control and Status A */
	uint8_t status_control_b; /* ucsr0b USART Control and Status B */
	uint8_t status_control_c; /* ucsr0c USART Control and Status C */
	uint8_t _reserved;
	uint8_t baud_rate_l; /* ubrr0l baud rate low */
	uint8_t baud_rate_h; /* ubrr0h baud rate high */
	uint8_t data_es;    /* udr0 i/o data */

} volatile uart_t;

volatile uart_t *kserial_port = (uart_t *) (0xc0);

void kserial_init() 
{
	/* conf High and Low registers using BAUD_PRESCALE */

	kserial_port->baud_rate_h = (unsigned char) (BAUD_PRESCALE>>8);
	kserial_port->baud_rate_l = (unsigned char) (BAUD_PRESCALE);

	/* 8bits frame, one parity bit and stop bit */
	kserial_port->status_control_c = (unsigned char)(INIT);

	/* activates transmision and reception */
	// serial_port->status_control_b = (unsigned char)(EN_RX_TX | (1<<UART_RXCIE0));
	kserial_port->status_control_b = (unsigned char)(EN_RX_TX);

}


void kserial_put_char (char outputChar)
{

	while (!((kserial_port->status_control_a) & (EN_TX)));
		kserial_port->data_es = outputChar;
}

char value;

/*
 * RX interrupt service rutine
 */
 ISR(USART_RX_vect){
 	value = UDR0;             /* read UART register into value */
//	// ttyhandler (1, value, 0);
 }

char kserial_get_char(void)
{
	/* Wait for the next character to arrive. */
	while (!((kserial_port->status_control_a) & (EN_RX)));
		return (kserial_port->data_es);
}

void kserial_put_str (char * msg)
{
	while (*msg) {
		kserial_put_char(*msg);
		msg++;
	};
}

