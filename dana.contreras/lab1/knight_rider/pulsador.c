
void delay_ms(volatile int ms);
unsigned char check_state();
unsigned char turn_on_leds(volatile unsigned char led_1, volatile unsigned char led_2, volatile unsigned char led_3);
void turn_off_leds(volatile unsigned char led_1, volatile unsigned char led_2, volatile unsigned char led_3);

volatile unsigned char* PIN_B = (unsigned char*) 0x23;
volatile unsigned char* DDR_B = (unsigned char*) 0x24;
volatile unsigned char* PORT_B = (unsigned char*) 0x25;

unsigned char button = 0x2; // 0000 0010

int main()
{
    unsigned char led_1 = 0x4; // 0000 0100 
    unsigned char led_2 = 0x8; // 0000 1000
    unsigned char led_3 = 0x10; // 0001 0000
    unsigned char state_button, state_while;

    *DDR_B = *DDR_B & (~button); // control: entrada.
    *PORT_B = button; // pull up.

    while(1){

        state_button = 0;
        state_while = 0;
        turn_off_leds(led_1,led_2,led_3);

        if(check_state()){ // Se presiona pulsador.

            delay_ms(100); // Rebote.

            if(check_state()){ // Se prenden luces.

                while (!state_while && !state_button) {
                    state_while = turn_on_leds(led_1,led_2,led_3);
                    if (!state_while)
                        state_while = turn_on_leds(led_3,led_2,led_1);

                    state_button = check_state();
                }
            }
        }
    }
    
    return 0;
}

void delay_ms(volatile int ms)
{
    volatile int i, max;

    max = ms * 301;
    for (i = 0; i < max; i++){}
}

unsigned char check_state()
{
    // Controla si el pulsador ha sido presionado.
    volatile unsigned char state = (*PIN_B & button);
    return (state != button);
}

unsigned char turn_on_leds(unsigned char led_1, unsigned char led_2, unsigned char led_3)
{

    int delay = 92;
    unsigned char state = 0;
    
    delay_ms(delay);
    *PORT_B = (*PORT_B | led_1); // led 1 encendido.
    delay_ms(delay);

    if (check_state())
        state = 1;

    *PORT_B = (*PORT_B | led_2); // led 2 prendido.
    *PORT_B = *PORT_B & (~led_1); // led 1 apagado.

    delay_ms(delay);
    
    if (check_state())
        state = 1;

    *PORT_B = (*PORT_B | led_3); // led 3 prendido.
    *PORT_B = (*PORT_B) & (~led_2); // led 2 apagado.
    delay_ms(delay);
                    
    if (check_state())
        state = 1;

    *PORT_B = *PORT_B & (~led_3); // led 3 apagado.
    delay_ms(delay);

    return state;
}

void turn_off_leds(unsigned char led_1, unsigned char led_2, unsigned char led_3)
{
    *PORT_B = *PORT_B & (~led_1) & (~led_2) & (~led_3);
}