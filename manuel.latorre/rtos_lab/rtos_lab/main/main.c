#include <xinu.h>
#include "serial.h"
#include "globals.h"
#include "timer1.h"
/* definicion de tareas (cuyo codigo fuente es externo) */

extern int main_motor(void);
extern int main_led_testigo(void);
extern int main_servo(void);
extern int main_rtc(void);
extern int main_show_data(void);

int main(void)
{
	char rcv_char=' ';
	serial_init();
	adc_init();
	timer1_init();
	*(DDR_B)|= 0b00100110;//bit 5= led arduino, salida pb1=motor y pb2=servo para PWM 
  *(PUERTO_B)&= 0b11011101;
	/* creamos y ponemos a ejecutar las tareas */
	
	resume(create(main_motor, 128, 30, "motr", 0));
	resume(create(main_led_testigo, 64, 30, "led", 0));
	resume(create(main_servo, 256, 30, "serv", 0));
	resume(create(main_rtc, 64, 30, "rtc", 0));
	resume(create(main_show_data, 64, 30, "rtc", 0));

	//serial_put_str("\rRTOS_LAB INICIADO\r\n");

	while(1) {
		if(serial_getchar_ready()){
			rcv_char= serial_get_char();
			if(rcv_char == 'n'){//Recibe n entonces enciende
				if(!motor_init) serial_put_str("\rMOTOR ENCENDIDO\r\n");
				motor_init=1;
			}else if(rcv_char == 'b'){
				if(motor_init) serial_put_str("\rMOTOR APAGADO\r\n");
				motor_init=0;
			}else if(rcv_char == 'a' || rcv_char == 'd' ){
				adjust_serv_angle(rcv_char);	
  		}
		}
		sleepms(1);
	}
	return 0;
}

void adjust_serv_angle(char rcv_char){
	if(rcv_char=='a'){
		if(serv_angle>0){
			serv_angle-=20;
		}
	}else if(rcv_char=='d'){
		if(serv_angle<180){
			serv_angle+=20;
		}
	}
}