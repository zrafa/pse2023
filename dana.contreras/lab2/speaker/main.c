#include "adc.h"
#include "delay.h"

void birthday_song();

/* notes */
int note_do = 191; //261;
int re = 170; //293;
int mi = 151; // 329;
int fa = 143; // 349;
int sol = 127; //392;
int la = 113; //440;
int si_bemol = 107; //466;
int si = 101; // 493;
int do_agudo = 95; // 523;

volatile unsigned char *DDR_B = (unsigned char *) 0x24;
volatile unsigned char *PORT_B = (unsigned char *) 0x25;
volatile unsigned char *PIN_B = (unsigned char *) 0x23;

void main() 
{
	/* portb bit cero. D8 en arduino */
	*DDR_B |= 0x1;

	adc_init();

	while (1) birthday_song();
	
	for(;;);
}

void note_time(int note, int dur) 
{
	int i = 0;
	int j = 0;
	int knob, high, low;

	knob = adc_get(0);
	low = (int)(note / ((knob + 100) * 0.024));
	high = note + note - low;

	while (j <= dur) {
		*PORT_B |= 0b1;
		for (i = 0; i < high; i++) delay_10us();
		*PORT_B ^= 0b1;
		for (i = 0; i < low; i++) delay_10us();

		j++;
	}

	delay_ms(100);

}

void birthday_song()
{
	note_time(note_do, 200);	
	note_time(note_do, 200);	
	note_time(re, 400);	
	note_time(note_do, 400);	
	note_time(fa, 400);	
	note_time(mi, 400);	

	note_time(note_do, 200);	
	note_time(note_do, 200);	
	note_time(re, 400);	
	note_time(note_do, 400);	
	note_time(sol, 400);	
	note_time(fa, 400);	

	note_time(note_do, 200);	
	note_time(note_do, 200);	
	note_time(do_agudo, 400);	
	note_time(la, 400);	
	note_time(fa, 400);	
	note_time(mi, 400);	
	note_time(re, 600);	

	note_time(si_bemol, 200);	
	note_time(si_bemol, 200);	
	note_time(la, 400);	
	note_time(fa, 400);	
	note_time(sol, 400);	
	note_time(fa, 800);

}