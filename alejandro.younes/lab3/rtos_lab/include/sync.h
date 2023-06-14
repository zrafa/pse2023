#include <xinu.h>

#ifndef _SYNC_H
#define _SYNC_H 

extern char semaforo[];

sync_wait(uint8 n);
sync_signal(uint8 n);
sync_set(uint8 n, char v);

#endif

