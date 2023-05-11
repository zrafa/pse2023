#include "adc.h"
#include "utils.h"

#define SPEAKER 0b00000001  // Positivo de speaker a PB0 (pin D8 Arduino Nano)
#define KNOB 0b00000000     // Pin medio de knob a ADC0 (pin A0 Arduino Nano)

/* NOTAS */
int nota_do = 191;   // 261;
int re = 170;        // 293;
int mi = 151;        // 329;
int fa = 143;        // 349;
int sol = 127;       // 392;
int la = 113;        // 440;
int si_bemol = 107;  // 466;
int si = 101;        // 493;
int do_agudo = 95;   // 523;

void nota_tiempo(int nota, int dur) {
    dur = dur / 4;  // 4 veces menos duración para escuchar mejor la canción
    nota = nota + adc_get(KNOB) / 64;  // 64 frecuencias posibles (4096/64 = 64)
    int i = 0;
    int j = 0;

    // Señal levantada dura lo mismo que bajada para hacer un ciclo
    while (j < dur) {
        levantar_pin_port_b(SPEAKER);
        for (i = 0; i < nota; i++)
            delay_10us();
        bajar_pin_port_b(SPEAKER);
        for (i = 0; i < nota; i++)
            delay_10us();
        j++;
    }
    delay_ms(200);  // Espera antes de la próxima nota
}

void cumple() {
    nota_tiempo(nota_do, 300);
    nota_tiempo(nota_do, 300);
    nota_tiempo(re, 500);
    nota_tiempo(nota_do, 500);
    nota_tiempo(fa, 500);
    nota_tiempo(mi, 500);

    nota_tiempo(nota_do, 300);
    nota_tiempo(nota_do, 300);
    nota_tiempo(re, 500);
    nota_tiempo(nota_do, 500);
    nota_tiempo(sol, 500);
    nota_tiempo(fa, 500);

    nota_tiempo(nota_do, 300);
    nota_tiempo(nota_do, 300);
    nota_tiempo(do_agudo, 500);
    nota_tiempo(la, 500);
    nota_tiempo(fa, 500);
    nota_tiempo(mi, 500);
    nota_tiempo(re, 700);

    nota_tiempo(si_bemol, 300);
    nota_tiempo(si_bemol, 300);
    nota_tiempo(la, 500);
    nota_tiempo(fa, 500);
    nota_tiempo(sol, 500);
    nota_tiempo(fa, 900);
}

void main() {
    inicializar_port_b();
    salida_pin_port_b(SPEAKER);
    adc_init();

    while (1) {
        cumple();

        nota_tiempo(nota_do, 500);
        nota_tiempo(re, 500);
        nota_tiempo(mi, 500);
        nota_tiempo(fa, 500);
        nota_tiempo(sol, 500);
        nota_tiempo(la, 500);
        nota_tiempo(si, 500);
    }
}
