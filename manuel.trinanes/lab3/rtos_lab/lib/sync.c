#include <xinu.h>
#include <avr/interrupt.h>

char semaforo[4];

sync_set(uint8 n, char v)
{
	uint8 x;

	x = disable();
	semaforo[n] = v;
	restore(x);
}

sync_wait(uint8 n)
{
	uint8 x;

	inicio:
	x = disable();
	if (semaforo[n] <= 0) {
		restore(x);
		sleepms(1);
		goto inicio;
	} 
	semaforo[n]--;
	restore(x);
}

sync_signal(uint8 n)
{
	uint8 x;

	x = disable();
	semaforo[n]++;
	restore(x);
}
