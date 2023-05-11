#include "sleep.h"
#include "adc.h"
#include "serial.h"

#define MAX_BRIGHTNESS 1024.0

int main()
{
    int rec, value;
    float temp;
    adc_init();
    serial_init();
    while (1)
    {
        rec = adc_get(0);
        temp = 1024.0 - rec;
        value = (int) (temp / 1024.0 * 100);
        serial_put_int(value, 3);
        serial_put_string("\n");
        sleep_ms_times(50, 10);
    }

    return 0;
}