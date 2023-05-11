/**********************************************************************
 *
 * Filename:    adc.h
 *
 * API para la aplicacion embebida
 * META : ocultar el hardware a la aplicacion
 *
 **********************************************************************/

#ifndef _ADC_H
#define _ADC_H

void adc_init(void);
int adc_get(int);

#endif  // _ADC_H
