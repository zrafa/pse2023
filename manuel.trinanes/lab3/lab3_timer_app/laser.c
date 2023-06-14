#include "timer.h"
#include "serial.h"
#include "adc.h"
#include <avr/interrupt.h>

void send_char(char c, int port_number, volatile unsigned char* port) {
    // Sets to low the light to start transmission
    *(port) ^= (1 << port_number);
    timer0_wait(100);

    // Sends the bits
    for (int i = 0; i < 8; i++) {
        // If the bit of the i position
        if ((c >> i) & 1) {
            *(port) |= 1 << port_number; // Is 1, high
        } else {
            *(port) ^= 1 << port_number; // Is 0, low
        }
        timer0_wait(100);
    }

    *(port) ^= 1 << port_number; // Sets to high again
}

#define NATURAL_LIGHT 3000
// For the arduino receptionist:
    char received_char;
char receive_char(int port){
    // serial_put_int(adc_get(2), 4);
    while(adc_get(port) > NATURAL_LIGHT);
    timer0_wait(50);
    timer0_wait(10);

    received_char = 0;
    for(int i=0; i < 8; i++){
        received_char |= (adc_get(port) > NATURAL_LIGHT) ? (1 << i) : (0 << i);
        timer0_wait(50);
    }

    while(adc_get(port) < NATURAL_LIGHT);
    
    return received_char;
}


int main(void) {
    volatile unsigned char * DDR_D = 0x2A;
    volatile unsigned char * PORT_D = 0x2B;

    int laser_port = 2;
    (*PORT_D) = 1 << laser_port;
    *(DDR_D) = 1 << laser_port;

    timer0_init();
    serial_init();
    adc_init();
    sei();
    char char_sent, char_received;
    while(1) {
        // Send
        // caracter = serial_get_char();
        // send_char(caracter, laser_port, DDR_D);

        // Receive
        char_received = receive_char(2);
        serial_put_char(char_received);
        serial_put_new_line();
        
    }
}