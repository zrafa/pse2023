// LED L (Nano) = D13 (Nano) = PB5 (328)

void main(void) {
    volatile unsigned char* DDR_B = (unsigned char*)0x24;
    volatile unsigned char* PUERTO_B = (unsigned char*)0x25;
    volatile unsigned long i;
    volatile unsigned long n = 376470UL;

    *DDR_B = 0b00100000;  // PB5 es salida

    while (1) {
        *PUERTO_B = 0b00000000;  // Pull-down PB
        for (i = 1UL; i <= n; i++) {
        }
        *PUERTO_B = 0b00100000;  // Pull-up PB5
        for (i = 1UL; i <= n; i++) {
        }
    }
}