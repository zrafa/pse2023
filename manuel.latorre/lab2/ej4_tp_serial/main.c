#include "serial.h"
#include "knight_rider.h"
#include "ultrasound.h"
#include "globals.h"
int main(void)
{   
    /* Configure the UART for the serial driver */
    serial_init();
    serial_put_string("EJECUTANDO.\r\n");
    serial_put_string("k: Inicio knightrider.\r\n");
    serial_put_string("u: Inicio ultrasound.\r\n");
    serial_put_string("q: Para finalizar cualquiera de los dos.\r\n");
    serial_put_char("\n");
    while (1)
    {
        // Wait for an incoming character 
        serial_put_string("\rIngrese una letra: ");
        rcv_char = serial_get_char();
        // Echo the character back along with a carriage return and line feed 
        
        serial_put_char(rcv_char);
        serial_put_char('\r');
        serial_put_char('\n');
        if(rcv_char == 'k'){
            knight_rider_run();
        }else if(rcv_char == 'u'){
            ultrasound_run();
        }
    }

    for (;;);
    return 0;
}

