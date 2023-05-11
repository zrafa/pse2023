#include "adc.h"
#include "serial.h"
#include "delay.h"

int brightness_control (int ldr);
void convert_to_string (char* str, int length, int num);

#define MAX_BRIGTHNESS 19200

int main()
{
    int ldr, data;
    int n = 6;
    char* str = "00000-";

    adc_init();
    serial_init();
    
    while (1){
        ldr = adc_get(0);
        data = brightness_control(ldr);
        convert_to_string(str,n,data);
        serial_put_str(str);
        delay_ms(200);
    }
    
    return 0;
}

int brightness_control (int ldr)
{
    int light, n;
    
    n = MAX_BRIGTHNESS / 12;
    light = MAX_BRIGTHNESS;

    while (ldr > 1){
        light -= n;
        ldr /= 2;
    }

    return light;
}

void convert_to_string (char* str, int length, int num)
{
    int i;

    str[length-1] = 45;
    for (i = length-2; i >= 0; i--) {
        str[i] = (char)(num % 10 + 48);
        num /= 10;
    }
}