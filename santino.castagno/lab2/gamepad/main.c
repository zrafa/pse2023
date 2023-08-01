#include <stdint.h>
#include "serial.h"
#include "sleep.h"
#include "adc.h"

#define INIT_DATA_DIRECTION 0x00
#define INIT_PULL_UP 0x03
#define HIGH_BTN_SHOOT 0x01

#define ADC_MAX_VALUE 1024
#define ADC_LEFT_MOVE (ADC_MAX_VALUE / 2) - 50
#define ADC_RIGHT_MOVE (ADC_MAX_VALUE / 2) + 50

volatile unsigned char *PIN_B = (unsigned char *)0x23;    // direccion de PIN_B
volatile unsigned char *DDR_B = (unsigned char *)0x24;    // direccion de DDR_B
volatile unsigned char *PUERTO_B = (unsigned char *)0x25; // direccion de PORT_B

int main()
{
    uint8_t input_btn;
    uint32_t input_adc;
    (*DDR_B) = INIT_DATA_DIRECTION;
    (*PUERTO_B) = INIT_PULL_UP;
    serial_init();
    adc_init();

    /* inf loop */
    while (1)
    {
        input_btn = (*PIN_B);

        input_adc = adc_get(0);
        // serial_put_int(input_adc, 4);
        // serial_put_string("\r\n");
        sleep_ms_times(20, 1);
        if (!(input_btn & HIGH_BTN_SHOOT))
        {
            switch (input_adc)
            {
            case 0 ... ADC_LEFT_MOVE:
                serial_put_char('3');
                // serial_put_char('\n');
                break;
            case ADC_LEFT_MOVE + 1 ... ADC_RIGHT_MOVE - 1:
                serial_put_char('5');
                // serial_put_char('\n');
                break;
            case ADC_RIGHT_MOVE ... ADC_MAX_VALUE:
                serial_put_char('4');
                // serial_put_char('\n');
                break;
            default:
                break;
            }
        }
        else
        {
            switch (input_adc)
            {
            case 0 ... ADC_LEFT_MOVE:
                serial_put_char('1');
                // serial_put_char('\n');
                break;
            case ADC_LEFT_MOVE + 1 ... ADC_RIGHT_MOVE - 1:
                serial_put_char('0');
                // serial_put_char('\n');
                break;
            case ADC_RIGHT_MOVE ... ADC_MAX_VALUE:
                serial_put_char('2');
                // serial_put_char('\n');
                break;
            default:
                break;
            }
        }
    };
    return 0;
}