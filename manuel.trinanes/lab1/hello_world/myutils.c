void delay_sec(unsigned int sec) {
    volatile long i;
    for(i = 0; i < sec * 180000; i++){
    }
}

void delay_ms(unsigned int ms) {
    volatile long i;
    for(i = 0; i < ms * 180; i++){
    }
}

void delay_10_us() {
    volatile int i = 0;
    i++;
}

void delay_us(int us) {
    int i = 0;
    while(i < us * 5) {
        i++;
    }
}