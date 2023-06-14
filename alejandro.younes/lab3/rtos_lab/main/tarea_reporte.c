#include <xinu.h>
#include "serial.h"

extern unsigned int timer2_velocidad_motor;
extern unsigned int timer1_angulo;
extern unsigned int timer1_segundo;
extern unsigned int timer1_minuto;
extern unsigned int timer1_hora;

int tarea_reporte() {
    unsigned int i;
    unsigned char str_rtc[46];
    unsigned int hor;
    unsigned int min;
    unsigned int seg;
    unsigned int vel;
    unsigned int ang;
    // inicializar caracteres fijos del mensaje
    str_rtc[2] = ':';
    str_rtc[5] = ':';
    str_rtc[8] = '.';
    str_rtc[9] = ' ';
    str_rtc[10] = 'v';
    str_rtc[11] = 'e';
    str_rtc[12] = 'l';
    str_rtc[13] = 'o';
    str_rtc[14] = 'c';
    str_rtc[15] = 'i';
    str_rtc[16] = 'd';
    str_rtc[17] = 'a';
    str_rtc[18] = 'd';
    str_rtc[19] = ':';
    str_rtc[20] = ' ';
    str_rtc[24] = '%';
    str_rtc[25] = '.';
    str_rtc[26] = ' ';
    str_rtc[27] = 's';
    str_rtc[28] = 'e';
    str_rtc[29] = 'r';
    str_rtc[30] = 'v';
    str_rtc[31] = 'o';
    str_rtc[32] = ':';
    str_rtc[33] = ' ';
    str_rtc[37] = ' ';
    str_rtc[38] = 'g';
    str_rtc[39] = 'r';
    str_rtc[40] = 'a';
    str_rtc[41] = 'd';
    str_rtc[42] = 'o';
    str_rtc[43] = 's';
    str_rtc[44] = '.';
    str_rtc[45] = '\0';
    // cada 1 segundo consultar valores del reloj, motor y servo
    while (1) {
        sleep(1);

        vel = timer2_velocidad_motor;
        ang = timer1_angulo;
        seg = timer1_segundo;
        min = timer1_minuto;
        hor = timer1_hora;

        str_rtc[0] = '0';
        str_rtc[1] = '0';
        str_rtc[3] = '0';
        str_rtc[4] = '0';
        str_rtc[6] = '0';
        str_rtc[7] = '0';
        str_rtc[21] = ' ';
        str_rtc[22] = ' ';
        str_rtc[23] = '0';
        str_rtc[34] = ' ';
        str_rtc[35] = ' ';
        str_rtc[36] = '0';

        i = 1;
        while(hor != 0) {
            str_rtc[i] = (hor % 10) + '0';
            hor /= 10;
            i--;
        }
        i = 4;
        while(min != 0) {
            str_rtc[i] = (min % 10) + '0';
            min /= 10;
            i--;
        }
        i = 7;
        while(seg != 0) {
            str_rtc[i] = (seg % 10) + '0';
            seg /= 10;
            i--;
        }
        i = 23;
        while(vel != 0) {
            str_rtc[i] = (vel % 10) + '0';
            vel /= 10;
            i--;
        }
        i = 36;
        while(ang != 0) {
            str_rtc[i] = (ang % 10) + '0';
            ang /= 10;
            i--;
        }

        serial_put_str(str_rtc);
    }
}
