#include "adc.h"
#include "sleeps.h"

/* NOTAS */
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


void nota_tiempo(int nota, int dur) 
{
	int i = 0;
	int j = 0;
	//la division es para tomar valores de 0 al 9
    int val = (adc_get(2)/380); 
	dur = dur - 100;

	while (1) {
		*(PORT_B) |= 0b1;
		for (i=0; i<val; i++) delay_10_us();
		*(PORT_B) ^= 0b1;
		for (i=0; i<nota-val; i++) delay_10_us();

		j++;
		if (j > dur)
			break;
	}
	delay_ms(200);
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
}


void main() 
{

	/* utilizamos portb bit cero. D8 en arduino */
	(* DDR_B) |= 1 << 0;
	//vamos a usar el knob para aumentar o disminuir el volumen del speaker 
	adc_init();
	while (1) {
		cumple();

		nota_tiempo(nota_do, 500);	
		nota_tiempo(re, 500);	
		nota_tiempo(mi, 500);	
		nota_tiempo(fa, 500);	
		nota_tiempo(sol, 500);	
		nota_tiempo(la, 500);	
		nota_tiempo(si, 500);	
	}

	for(;;);

}