volatile unsigned char* PIN_B = (unsigned char*)0x23;
volatile unsigned char* DDR_B = (unsigned char*)0x24;
volatile unsigned char* PRT_B = (unsigned char*)0x25;

volatile unsigned char* PIN_D = (unsigned char*)0x29;
volatile unsigned char* DDR_D = (unsigned char*)0x2A;
volatile unsigned char* PRT_D = (unsigned char*)0x2B;

void portb_init() {
    *PRT_B = 0b00000000;
    *DDR_B = 0b00000000;
}

void portb_como_salida_pin(unsigned char numero) {
    *DDR_B |= numero;
}

void portb_como_entrada_pin(unsigned char numero) {
    *DDR_B &= ~numero;
}

void portb_subir_pin(unsigned char numero) {
    *PRT_B |= numero;
}

void portb_bajar_pin(unsigned char numero) {
    *PRT_B &= ~numero;
}

void portb_cambiar_pin(unsigned char numero) {
    *PRT_B ^= numero;
}

unsigned int portb_leer_pin(unsigned char numero) {
    return *PIN_B & numero;
}

void portd_init() {
    *PRT_D = 0b00000000;
    *DDR_D = 0b00000000;
}

void portd_como_salida_pin(unsigned char numero) {
    *DDR_D |= numero;
}

void portd_como_entrada_pin(unsigned char numero) {
    *DDR_D &= ~numero;
}

void portd_subir_pin(unsigned char numero) {
    *PRT_D |= numero;
}

void portd_bajar_pin(unsigned char numero) {
    *PRT_D &= ~numero;
}

void portd_cambiar_pin(unsigned char numero) {
    *PRT_D ^= numero;
}

unsigned int portd_leer_pin(unsigned char numero) {
    return *PIN_D & numero;
}
