//  8 (Uno) =  D8 (Nano) = PB0 (328P)
// 10 (Uno) = D10 (Nano) = PB2 (328P)
// 11 (Uno) = D11 (Nano) = PB3 (328P)
// 12 (Uno) = D12 (Nano) = PB4 (328P)

#define BOTON 0b00000001  // PB0 conectado a pulsador
#define LED_1 0b00000100  // PB2 conectado a ánodo 1er LED
#define LED_2 0b00001000  // PB3 conectado a ánodo 2do LED
#define LED_3 0b00010000  // PB4 conectado a ánodo 3er LED

volatile unsigned char* PIN_B = (unsigned char*)0x23;
volatile unsigned char* DDR_B = (unsigned char*)0x24;
volatile unsigned char* PRT_B = (unsigned char*)0x25;

void levantar_pin_port_b(unsigned char numero) {
    *PRT_B = *PRT_B | numero;
}

void bajar_pin_port_b(unsigned char numero) {
    *PRT_B = *PRT_B & ~numero;
}

unsigned int se_apago(unsigned int activo) {
    if (activo == 0) {
        bajar_pin_port_b(LED_1);
        bajar_pin_port_b(LED_2);
        bajar_pin_port_b(LED_3);
        return 1;
    }
    return 0;
}

void main(void) {
    volatile unsigned long i;
    unsigned int activo;

    *PRT_B = 0b00100001;  // pull-up PB0 y encender LED placa
    *DDR_B = 0b00111100;  // PB0 entrada PB2/3/4/5 salida

    while (1) {
        activo = 0;
        for (i = 0; i < 100000; i++) {   // detectar pulsación encedido
            activo = !(*PIN_B & BOTON);  // señal baja activa LEDs
        }
        while (activo) {
            levantar_pin_port_b(LED_1);
            for (i = 0; i < 100000; i++) {  // detectar pulsación apagado
                activo = *PIN_B & BOTON;    // señal baja apaga LEDs
            }
            if (se_apago(activo))
                break;
            bajar_pin_port_b(LED_1);
            levantar_pin_port_b(LED_2);
            for (i = 0; i < 100000; i++) {
                activo = *PIN_B & BOTON;
            }
            if (se_apago(activo))
                break;
            bajar_pin_port_b(LED_2);
            levantar_pin_port_b(LED_3);
            for (i = 0; i < 100000; i++) {
                activo = *PIN_B & BOTON;
            }
            if (se_apago(activo))
                break;
            bajar_pin_port_b(LED_3);
            levantar_pin_port_b(LED_2);
            for (i = 0; i < 100000; i++) {
                activo = *PIN_B & BOTON;
            }
            if (se_apago(activo))
                break;
            bajar_pin_port_b(LED_2);
        }
    }
}