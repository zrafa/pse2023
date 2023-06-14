#include <xinu.h>

extern unsigned int rtc_seconds;

int rtc(void)
{
	while(1) {
        rtc_seconds++;
		sleep(1);
	}
}
