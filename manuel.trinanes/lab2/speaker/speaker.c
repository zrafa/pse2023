#include "adc.h"
#include "myutils.h"

// Notes
int nota_do = 191; //261;
int re = 170; //293;
int mi = 151; // 329;
int fa = 143; // 349;
int sol = 127; //392;
int la = 113; //440;
int si_bemol = 107; //466;
int si = 101; // 493;
int do_agudo = 95; // 523;

volatile unsigned char *DDR_B = 0x24;
volatile unsigned char *PORT_B = 0x25;
volatile unsigned char *PIN_B = 0x23;

void note_time(int note, int dur) {
	int i = 0;
	int j = 0;
    int vol = (adc_get(2) / 455);
    dur = dur / 3;

	while (1) {
        // High until vol (0-9)
		*(PORT_B) |= 0b1;
		for (i=0; i<vol; i++) delay_10_us();
        // Down until note*2 (for complete period of the note) less the high part
		*(PORT_B) ^= 0b1;
		for (i=0; i<note*2-vol; i++) delay_10_us();

        // Duration of the note
		j++;
		if (j > dur)
			break;
	}
	delay_ms(200);
}

void happy_birthday() {
		note_time(nota_do, 300);	
		note_time(nota_do, 300);	
		note_time(re, 500);	
		note_time(nota_do, 500);	
		note_time(fa, 500);	
		note_time(mi, 500);	

		note_time(nota_do, 300);	
		note_time(nota_do, 300);	
		note_time(re, 500);	
		note_time(nota_do, 500);	
		note_time(sol, 500);	
		note_time(fa, 500);	

		note_time(nota_do, 300);	
		note_time(nota_do, 300);	
		note_time(do_agudo, 500);	
		note_time(la, 500);	
		note_time(fa, 500);	
		note_time(mi, 500);	
		note_time(re, 700);	

		note_time(si_bemol, 300);	
		note_time(si_bemol, 300);	
		note_time(la, 500);	
		note_time(fa, 500);	
		note_time(sol, 500);	
		note_time(fa, 900);	
}

void main() {
	(*DDR_B) |= 1 << 0;

    adc_init();

	while (1) {
		happy_birthday();

		note_time(nota_do, 500);	
		note_time(re, 500);	
		note_time(mi, 500);	
		note_time(fa, 500);	
		note_time(sol, 500);	
		note_time(la, 500);	
		note_time(si, 500);	
	}

	for(;;);
}