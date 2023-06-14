/**********************************************************************
 *
 * serial.c - Driver del UART del atmega328p
 *
 * META : ocultar el hardware a la aplicacion 
 *
 * Configuracion: 9600bps, 8bits data, 1bit stop, sin bit de paridad
 *
 **********************************************************************/

#include <stdint.h> /* para los tipos de datos. Ej.: uint8_t */

/* Completar la estructura de datos para que se superponga a los registros
   del periferico de hardware del USART del atmega328, segun sugerido
   en el apunte */

typedef struct
{
    uint8_t status_control_a;    /* ucsr0a USART Control and Status A */
    uint8_t status_control_b;    /* ucsr0b USART Control and Status B */
    uint8_t status_control_c;    /* ucsr0c USART Control and Status C */
    uint8_t _reserved;           /* espacio sin utilizar */
    uint8_t baud_rate_l;         /* ubrr0l baud rate low */
    uint8_t baud_rate_h;         /* ubrr0h baud rate high */ 
    uint8_t data_es;             /* udr0 i/o data */
} volatile uart_t;

/* puntero a la estructura de los registros del periferico */
uart_t *puerto_serial = (uart_t *) (0xc0);

#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU/(USART_BAUDRATE*16UL)))-1) /* F_CPU viene como paramentro en el Makefile */

/* UCSRnC */

/* the UCSZn bits combined with the UCSZn2 bit in UCSRnB sets the number of data bits */
/* in a frame the receiver and transmitter use */
#define FRAME_SIZE_0 0x02 /* 0b 0000 0010 - bit 1 */
#define FRAME_SIZE_1 0x04 /* 0b 0000 0100 - bit 2 */

/* USBSn (bit 3) selects the number of stop bits to be inserted by the transmitter (0 is 1 bit) */
/* UPMn these bits set the type of parity generation and check (0 and 0 is disabled) */

/* UCSRnB */

/* the RXENn bit if set to one enables the USART receiver */
#define RECEIVER_ENABLE 0x10 /* 0b 0001 0000 - bit 4  */

/* the TXENn bit if set to one enables the USART transmitter */
#define TRANSMITTER_ENABLE 0x08 /* 0b 0000 1000 - bit 3 */

/* UCSRnA */

/* the RXCn bit is set when there are unread data in the receive buffer */
/* and cleared when the receibe buffer is empty (ie does not contain any unread data */
#define READY_TO_READ 0x80 /* 0b 1000 0000 - bit 7 */

/* the UDREn flag indicates if the transmit buffer is ready to receive new data */
/* if UDREn is one, the buffer is empty and therefore ready to be written */
#define READY_TO_WRITE 0x20  /* 0b 0010 0000 - bit 5 */


void serial_init()
{
    /* Configurar los registros High y Low con BAUD_PRESCALE */
    puerto_serial->baud_rate_h = (unsigned char) (BAUD_PRESCALE>>8);
    puerto_serial->baud_rate_l = (unsigned char) (BAUD_PRESCALE);

    /* Configurar un frame de 8bits, sin bit de paridad y un bit de stop */
    puerto_serial->status_control_c = (unsigned char) (FRAME_SIZE_0 + FRAME_SIZE_1);

    /* Activar la recepcion y transmision */
    puerto_serial->status_control_b = (unsigned char) (RECEIVER_ENABLE + TRANSMITTER_ENABLE);
}


/* enviar un byte a traves del dispositivo inicializado */
void serial_put_char(char c)
{
    /* Wait until the transmitter is ready for the next character. */

    /* Se debe esperar verificando el bit UDREn del registro UCSRnA,
        hasta que el buffer esté listo para recibir un dato a transmitir */
    while ( !((puerto_serial->status_control_a) & (READY_TO_WRITE)) );

    /* Send the character via the serial port. */
    /* (escribir el dato al registro de datos de E/S */
    puerto_serial->data_es = c;
}


char serial_get_char(void)
{
    /* Wait for the next character to arrive. */
    /* Completar con E/S programada similar a serial_put_char pero 
       utilizando el bit correcto */
    while ( !((puerto_serial->status_control_a) & (READY_TO_READ)) );

    /* DEBE devolver el valor que se encuentra en el registro de datos de E/S */
    return (puerto_serial->data_es);
}


void serial_put_str(char * str)
{
    while (*str) {
        serial_put_char(*str);
        str++;
    }
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
