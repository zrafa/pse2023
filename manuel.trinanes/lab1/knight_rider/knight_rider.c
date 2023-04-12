void delay(long delay) {
    volatile long i;
    for(i = 0; i < delay; i++){
    }
}

int main(void) {
    volatile unsigned char * DDR_B = 0x24;
    volatile unsigned char * PORT_B = 0x25;
    volatile unsigned char * PIN_B = 0x23;
    volatile unsigned char * DDR_D = 0x2A;
    volatile unsigned char * PORT_D = 0x2B;

    // Integrated led
    int portOutput = 5;
    *(DDR_B) |= 1 << portOutput;

    // Input pullup
    int portInput = 4;
    *(PORT_B) |= 1 << portInput;

    // Lights
    char lightbar = 0;
    int lights = 0b00000111;
    char ida = 1;
    *(DDR_D) |= 0b111111 << 2; 
    *(DDR_B) |= 0b11;

    while(1) {
        if((*(PIN_B) & (1 << portInput)) == 0) {
            delay(10000);
            if((*(PIN_B) & (1 << portInput)) == 0) {
                lightbar = !lightbar;
                *(PORT_B) ^= 1 << portOutput;
                delay(100000);
            }
        }

        if(lightbar) {
            *(PORT_D) = lights << 2 | (*(PORT_D) & 0b11);
            *(PORT_B) = (*(PORT_B) & (0b111111 << 2)) | lights >> 6;
            if(ida) {
                lights <<= 1;
            } else {
                lights >>= 1;
            }
            if((lights & 1) || (lights & (1 << 7))){
                ida = !ida;
            }
            delay(50000);
        }
    }

    return 0;
}
