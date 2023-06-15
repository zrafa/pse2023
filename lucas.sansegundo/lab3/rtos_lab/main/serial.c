
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
    uint8_t status_control_b;    /* ucsr0c USART Control and Status B */
    uint8_t status_control_c;    /* ucsr0c USART Control and Status C */
    uint8_t _reserved; /* espacio sin utilizar */
    uint8_t baud_rate_l; /* ubrr0l baud rate low */;
    uint8_t baud_rate_h; /* ubrr0h baud rate high */
    uint8_t data_es; /* udr0 i/o data */
    /* demas registros */

} volatile uart_t;

/* puntero a la estructura de los registros del periferico */
uart_t *puerto_serial = (uart_t *) (0xc0);



#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU/(USART_BAUDRATE*16UL)))-1)
#define INIT 0b00000110 
//baud rate de 2400 bits por segundo, 8bits de datos, sin bit de paridad, y un bit de stop.

//------

#define RECEIVER_ENABLE 0x10 /* RXEN0 Habilitar la recepcion */
#define TRANSMITTER_ENABLE 0x08 /* TXEN0 Habilitar la transmicion */
#define CHARACTER_SIZE_0 0x20 /* UCSZ00 Numero de bits del dato de e/s */
#define CHARACTER_SIZE_1 0x40 /* UCSZ01 Numero de bits del dato de e/s */
#define READY_TO_READ 0x80 /* RXC0 Dato listo para leer */
#define READY_TO_WRITE 0x20 /* UDRE0 Buffer vacio listo para escribir */

void serial_init() {

	/* Escribir una rutina de inicializacion */

	/* El manual del atmega328p tiene un ejemplo. Adecuarla a C y la estructura de datos */

	/* Configurar los registros High y Low con BAUD_PRESCALE */
    puerto_serial->baud_rate_h = (unsigned char) (BAUD_PRESCALE>>8);
    puerto_serial->baud_rate_l = (unsigned char) (BAUD_PRESCALE);

	/* Configurar un frame de 8bits, con un bit de paridad y bit de stop */
    puerto_serial->status_control_c = (unsigned char) (INIT);
    

	/* Activar la recepcion y transmicion */
    puerto_serial->status_control_b = (unsigned char) (RECEIVER_ENABLE|TRANSMITTER_ENABLE);


}


/* enviar un byte a traves del del dispositivo inicializado */
void serial_put_char (char c)
{
    /* Wait until the transmitter is ready for the next character. */

    /* completar con E/S programada */
    /* Se debe esperar verificando el bit UDREn del registro UCSRnA,
       hasta que el buffer esté listo para recibir un dato a transmitir */

    while(!((puerto_serial->status_control_a) & (READY_TO_WRITE)));
    // while ( /* completar con E/S programada */ )
    //     ;

    /* Send the character via the serial port. */
    /* (escribir el dato al registro de datos de E/S */
    puerto_serial->data_es = (unsigned char) c;


}


char serial_get_char(void)
{
    /* Wait for the next character to arrive. */
    /* Completar con E/S programada similar a serial_put_char pero 
       utilizando el bit correcto */
    
    // while ( /* completar con E/S programada */ )
     while(!((puerto_serial->status_control_a) & (READY_TO_READ)));
    

    // return /* DEBE devolver el valor que se encuentra en el registro de datos de E/S */
    return (puerto_serial->data_es);

}

void serial_put_str(const char* string) 
{
    int lenght = strlen(string);
    for(int i=0; i<lenght; i++) {
        serial_put_char(string[i]);
    }
}

int serial_getchar_ready(void)
{
    return ((puerto_serial->status_control_a & (1 << 7)));
}

void serial_put_int(int value, int cant_digitos)
{
    char digits[cant_digitos];

    for(int i = 0; i < cant_digitos; i++){
        if(value > 0){
            digits[i] = (value % 10) + 48;
            value = value / 10;
        } else {
            digits[i] = 48;
        }
    }

    for (int j = cant_digitos-1; j >= 0; j--) {
        serial_put_char(digits[j]);
    }
}



