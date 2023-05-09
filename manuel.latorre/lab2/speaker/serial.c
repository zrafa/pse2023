
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
    uint8_t status_control_b; 
    uint8_t status_control_c;    /* ucsr0c USART Control and Status C */
    uint8_t _reserved;           /* espacio sin utilizar */
    uint8_t baud_rate_l;         /* ubrr0l baud rate low */;
    uint8_t baud_rate_h;         /* ubrr0h baud rate high */
    uint8_t data_es;             /* udr0 i/o data */

} volatile uart_t;

/* puntero a la estructura de los registros del periferico */
uart_t *puerto_serial = (uart_t *) (0xc0);



#define USART_BAUDRATE 2400
#define BAUD_PRESCALE (((F_CPU/(USART_BAUDRATE*16UL)))-1)

void serial_init() {

	/* Escribir una rutina de inicializacion */

	/* El manual del atmega328p tiene un ejemplo. Adecuarla a C y
           la estructura de datos */

	/* Configurar los registros High y Low con BAUD_PRESCALE */
    puerto_serial->baud_rate_l = (uint8_t)BAUD_PRESCALE;
    puerto_serial->baud_rate_h = (uint8_t)(BAUD_PRESCALE >> 8);

    /* Activar la recepcion y transmicion */
    puerto_serial->status_control_b = (1 << 3) | (1 << 4) | (0 << 2);
    /*
    (1 << 3) el bit 3(TXEN0) activa la transmision 
    (1 << 4) bit 4 (RXEN0) Actiba la recepcion
    (0 << 2) para establecer los 8 bits
    */

	/* Configurar un frame de 8bits, con un bit de paridad y bit de stop */
    //puerto_serial->status_control_c = (1 << 1) | (1 << 2) | (0 << 3) | (0 << 6);

    puerto_serial->status_control_c = (0 << 5) | (0 << 4) | (1 << 2) | (1 << 1);
    /*
        (0 << 5) 
        (0 << 4) Setean la paridad

        (1 << 2)
        (1 << 1) establecen 8 bits junto con el bit 2 de controlportb bit 2=0
    */
}


/* enviar un byte a traves del del dispositivo inicializado */
void serial_put_char (char c)
{
    while(!(puerto_serial->status_control_a & (1 << 5))){ //bit 5: data registry empty
    }
    puerto_serial->data_es = c; //Guarda el char en el buffer
}

void serial_put_int(int value, int cant_digitos)
{
    char buffer[cant_digitos]; 
    sprintf(buffer, "%d", value); // convierte el entero en una cadena de caracteres

    for (int i = 0; buffer[i] != '\0'; i++) { // envía cada carácter de la cadena a través del UART
        serial_put_char(buffer[i]);
    }
}

void serial_put_string(const char* str) 
{
    int len = strlen(str);
    for(int i=0; i<len; i++) {
        serial_put_char(str[i]);
    }
}

char serial_get_char(void)
{
    /* Wait for the next character to arrive. */
    while(!(puerto_serial->status_control_a & (1 << 7)));//bit 7: data receive completed
    return puerto_serial->data_es;
    
}

int serial_getchar_ready(void)
{
    return ((puerto_serial->status_control_a & (1 << 7)));
}