volatile unsigned char* PIN_B = (unsigned char*)0x23;
volatile unsigned char* DDR_B = (unsigned char*)0x24;
volatile unsigned char* PRT_B = (unsigned char*)0x25;

// espera n milisegundos
void delay_ms(unsigned int n) {
    volatile long i;
    for (i = 0; i < n * 180; i++) {
    }
}

// espera 10 microsegundos
void delay_10us() {
    volatile int i = 0;
    i++;
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

void levantar_pin_port_b(unsigned char numero) {
    *PRT_B = *PRT_B | numero;
}

void bajar_pin_port_b(unsigned char numero) {
    *PRT_B = *PRT_B & ~numero;
}

unsigned int leer_pin_port_b(unsigned char numero) {
    return *PIN_B & numero;
}
