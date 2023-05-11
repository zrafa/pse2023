#include "adc.h"
#include "serial.h"
#include "sleep.h"

/* NOTAS */
int nota_do = 191;  // 261;
int re = 170;       // 293;
int mi = 151;       // 329;
int fa = 143;       // 349;
int sol = 127;      // 392;
int la = 113;       // 440;
int si_bemol = 107; // 466;
int si = 101;       // 493;
int do_agudo = 95;  // 523;

volatile unsigned char(*DDR_B) = (unsigned char *)0x24;
volatile unsigned char(*PORT_B) = (unsigned char *)0x25;
volatile unsigned char(*PIN_B) = (unsigned char *)0x23;

#define MAX_VALUE_POT 867.0

/* usamos D8 arduino nano, portb, bit cero */
void nota_tiempo(int nota, int dur)
{
    int i = 0, j = 0, lim_h, lim_l, temp, vol = obtener_volumen();
    temp = (int)((float)vol / 10);
    lim_h = temp;
    lim_l = nota * 2 - temp;
    while (1)
    {
        (*PORT_B) |= 0b1;
        for (i = 0; i < lim_h; i++)
            sleep_nano_10us();

        (*PORT_B) ^= 0b1;
        for (i = 0; i < lim_l; i++)
            sleep_nano_10us();

        j++;
        if (j > dur)
            break;
    }
    sleep_ms(51);
}

int obtener_volumen()
{
    int vol, rec = adc_get(0);

    vol = (rec / MAX_VALUE_POT) * 100;

    return vol;
}

void cumple()
{
    nota_tiempo(nota_do, 300);
    nota_tiempo(nota_do, 300);
    nota_tiempo(re, 500);
    nota_tiempo(nota_do, 500);
    nota_tiempo(fa, 500);
    nota_tiempo(mi, 500);

    nota_tiempo(nota_do, 300);
    nota_tiempo(nota_do, 300);
    nota_tiempo(re, 500);
    nota_tiempo(nota_do, 500);
    nota_tiempo(sol, 500);
    nota_tiempo(fa, 500);

    nota_tiempo(nota_do, 300);
    nota_tiempo(nota_do, 300);
    nota_tiempo(do_agudo, 500);
    nota_tiempo(la, 500);
    nota_tiempo(fa, 500);
    nota_tiempo(mi, 500);
    nota_tiempo(re, 700);

    nota_tiempo(si_bemol, 300);
    nota_tiempo(si_bemol, 300);
    nota_tiempo(la, 500);
    nota_tiempo(fa, 500);
    nota_tiempo(sol, 500);
    nota_tiempo(fa, 900);

    nota_tiempo(nota_do, 500);
    nota_tiempo(re, 500);
    nota_tiempo(mi, 500);
    nota_tiempo(fa, 500);
    nota_tiempo(sol, 500);
    nota_tiempo(la, 500);
    nota_tiempo(si, 500);
}

void main()
{
    /* utilizamos portb bit cero. D8 en arduino */
    (*DDR_B) |= 1 << 0;
    serial_init();
    adc_init();

    while (1)
    {
        cumple();
    }

    for (;;)
        ;
}