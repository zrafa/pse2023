
/**********************************************************************
 *
 * serial.c - Driver del UART of atmega328p
 *
 * Objective : hide hardware form app 
 *
 * Configured: 2400bps, 8-bit data frame, 1-bit stop, 1-bit parity, 4MHz of clock speed
 *
 **********************************************************************/

#include <stdint.h>

typedef struct {
    uint8_t status_control_a;   // ucsr0a USART Control and Status A
    uint8_t status_control_b;   // ucsr0b USART Control and Status B 
    uint8_t status_control_c;   // ucsr0c USART Control and Status C
    uint8_t reserved;           // unused space to align registers with structure
    uint8_t baud_rate_l;        // ucsr0l baud rate low 
    uint8_t baud_rate_h;        // ucsr0h baud rate high 

    uint8_t data_es;            // udr0 i/o data
} volatile uart_t;

// Pointer to peripheral register data structure
uart_t *serial_port = (uart_t *) (0xc0);

#define F_CPU 4000000UL
#define USART_BAUDRATE 2400
#define BAUD_PRESCALE (((F_CPU/(USART_BAUDRATE*16UL)))-1)
/*
7:6 Asynchronous (00)
5:4 Even Parity (10)
3   1 stop bit (0)
2:1 8-bit size (11)
0   Falling Edge (0)
*/ 
#define USART_INIT ((0b00 << 6) | (0b10 << 4) | (0b0 << 3) | (0b11 << 1) | (0b0 << 0))
#define ENABLE_RX_TX (0b11 << 3)
#define UDREn 1 << 5
#define RXCn 1 << 7

void serial_init() {
	// Configure High and Low registers with BAUD_PRESCALE
    serial_port->baud_rate_h = (unsigned char) (BAUD_PRESCALE >> 8);
    serial_port->baud_rate_l = (unsigned char) (BAUD_PRESCALE);

	// Configure 8-bits frame, parity and 1-bit stop
    serial_port->status_control_c = (unsigned char) (USART_INIT);

    // Enables the Rx and Tx
    serial_port->status_control_b = (unsigned char) (ENABLE_RX_TX);
}

void serial_put_char (char c) {
    // Wait until the transmitter is ready for the next character.
    while (!(serial_port->status_control_a & UDREn));

    // Send the character via the serial port.
    serial_port->data_es = c;
}

void serial_put_int (int num, int length) {
    char digits[length];

    for(int i = 0; i < length; i++){
        if(num > 0){
            digits[i] = (num % 10) + 48;
            num = num / 10;
        } else {
            digits[i] = 48;
        }
    }

    for (int j = length-1; j >= 0; j--) {
        serial_put_char(digits[j]);
    }
}

void serial_put_new_line () {
    serial_put_char('\n');
    serial_put_char('\r');
}

void serial_put_start () {
    serial_put_char('s');
    serial_put_char('t');
    serial_put_char('a');
    serial_put_char('r');
    serial_put_char('t');
}

char serial_get_char(void) {
    // Wait for data to be received
    while (!(serial_port->status_control_a & RXCn));

    // Get and return received data from buffer
    return serial_port->data_es;
}

char serial_try_get_char (void) {
    if(serial_port->status_control_a & RXCn) {
        return serial_port->data_es;
    }
    return 0;
}