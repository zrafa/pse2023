#include <stdint.h>

typedef struct {
    uint8_t adcl;
    uint8_t adch;
    uint8_t adcsra;
    uint8_t adcsrb;
    uint8_t admux;
    uint8_t reserved;
    uint8_t didr0;
} volatile adc_t;

adc_t *adc = (adc_t *) (0x78);

#define ADSC 6
#define ADIF 4

void adc_init() {
    // ADMUX to AVcc with external capacitor and ADLAR (5th bit) to 0 for 10-bit
    adc->admux = (0b01 << 6) | (0 << 5);

    // ADEN to 1 (enables ADC) and 0b101 for 32 division factor
    adc->adcsra = (1 << 7) | (0b101);
}

int adc_get(char input) {
    // Input to 4 bits of the desired input port
    adc->admux |= (input & 0b1111);

    // Starts conversion
    adc->adcsra |= (1 << ADSC);

    // While the ADC interrupt flag is 0
    while(!((adc->adcsra) & (1 << ADIF)));

    // Returns shifted high bits to 8 and lower bits
    uint8_t low = adc->adcl;
    uint8_t high = adc->adch;

    return (high << 8) | low;
}
