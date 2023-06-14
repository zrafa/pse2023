volatile unsigned char* PIN_B = (unsigned char*)0x23;
volatile unsigned char* DDR_B = (unsigned char*)0x24;
volatile unsigned char* PRT_B = (unsigned char*)0x25;

volatile unsigned char* PIN_D = (unsigned char*)0x29;
volatile unsigned char* DDR_D = (unsigned char*)0x2A;
volatile unsigned char* PRT_D = (unsigned char*)0x2B;

// espera n milisegundos
void delay_ms(unsigned int n) {
    // 1000 ms = 376470 iteraciones vacias (328P a 16MHz)
    volatile unsigned long i;
    volatile unsigned long m = (n * 376470UL) / 1000UL;

    for (i = 1UL; i <= m; i++) {
    }
}

// espera 10 microsegundos
void delay_10us() {
    // 1000 us = 376 iteraciones vacias (328P a 16MHz)
    // 10 us * 376 iteraciones / 1000 us =~ 4 iteraciones
    volatile unsigned int i;
    volatile unsigned int m = 4U;

    for (i = 1U; i <= m; i++) {
    }
}

void inicializar_port_b() {
    *PRT_B = 0b00000000;
    *DDR_B = 0b00000000;
}

void salida_pin_port_b(unsigned char numero) {
    *DDR_B = *DDR_B | numero;
}

void entrada_pin_port_b(unsigned char numero) {
    *DDR_B = *DDR_B & ~numero;
}

void subir_pin_port_b(unsigned char numero) {
    *PRT_B = *PRT_B | numero;
}

void bajar_pin_port_b(unsigned char numero) {
    *PRT_B = *PRT_B & ~numero;
}

void cambia_pin_port_b(unsigned char numero) {
    *PRT_B = *PRT_B ^ numero;
}

unsigned int leer_pin_port_b(unsigned char numero) {
    return *PIN_B & numero;
}

void inicializar_port_d() {
    *PRT_D = 0b00000000;
    *DDR_D = 0b00000000;
}

void salida_pin_port_d(unsigned char numero) {
    *DDR_D = *DDR_D | numero;
}

void entrada_pin_port_d(unsigned char numero) {
    *DDR_D = *DDR_D & ~numero;
}

void subir_pin_port_d(unsigned char numero) {
    *PRT_D = *PRT_D | numero;
}

void bajar_pin_port_d(unsigned char numero) {
    *PRT_D = *PRT_D & ~numero;
}

void cambia_pin_port_d(unsigned char numero) {
    *PRT_D = *PRT_D ^ numero;
}

unsigned int leer_pin_port_d(unsigned char numero) {
    return *PIN_D & numero;
}
