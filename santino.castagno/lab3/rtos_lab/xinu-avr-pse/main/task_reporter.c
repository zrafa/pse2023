
#include <xinu.h>
#include "serial.h"
#include "timer1.h"

extern unsigned char motor_speed;
extern unsigned char servo_angle;
extern unsigned char seg;
extern unsigned char min;
extern unsigned char hor;
/**
 * tarea encargada de recibir la entrada del operador
 */
int reporter(void)
{
    while (1)
    {
        serial_put_int(hor, 2);
        serial_put_str(":");
        serial_put_int(min, 2);
        serial_put_str(":");
        serial_put_int(seg, 2);
        serial_put_str(" velocidad ");
        serial_put_int(motor_speed, 3);
        serial_put_str("%.");
        serial_put_str(" servo ");
        serial_put_int(servo_angle, 3);
        serial_put_str(" grados.");
        serial_put_str("\n\r");
        sleep(1);
    }
}
