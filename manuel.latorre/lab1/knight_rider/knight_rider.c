volatile unsigned char * DDR_B = (unsigned char *) 0x24;
volatile unsigned char * PUERTO_B = (unsigned char *) 0X25;
volatile unsigned char * PIN_B= (unsigned char *) 0X23;
int encendido=0;
int apretado=0;

int main(void)
{
  (*DDR_B)= 0b00100111;//bit 5= led arduino(para debugear),pb3= ENTRADA, pb0,pb1,pb2=SALIDAS
  (*PUERTO_B)= 0b00001001;//Habilita pullup en pin pb3 y enciende pin pb0
  
  while(1){
    encender_apagar();
    while(encendido==0){encender_apagar();} //Con esto me aseguro que siempre arranca aca cada vez que apreta el boton
      if(encendido==1){
        esperar(); //delay prendido
        (*PUERTO_B)= (*PUERTO_B) & 0b11111110;//Apaga pb0=d8
        esperar();//delay apagado
      }

      if(encendido==1){
        (*PUERTO_B)= (*PUERTO_B) | 0b00000010;//Prende pb1=d9
        esperar();//delay prendido
      }

      if(encendido==1){
        (*PUERTO_B)= (*PUERTO_B) & 0b11111101;//Apaga pb1=d9
        esperar();//delay apagado
      }

      if(encendido==1){
        (*PUERTO_B)= (*PUERTO_B) | 0b00000100;//Prende pb2=d10
        
        esperar();//delay prendido
      }

      if(encendido==1){
        (*PUERTO_B)= (*PUERTO_B) & 0b11111011;//Apaga pb2=d10
        
        esperar();//delay apagado
      }
      if(encendido==1){
        (*PUERTO_B)= (*PUERTO_B) | 0b00000001;//Prende pb0=d8
      }

  }
}

void encender_apagar()
{
  volatile int bit_in = (*PIN_B) & 0b00001000;
  volatile long i=0;
  
  if(bit_in==0 && apretado==0){//Si apretó y no venia pulsando 
    for(i=0; i<10000; i++){} 
    if(encendido==0){//Si estaba apagado lo prende (Aca yo decidi que vuelva a empezar siempre al encenderse y que no arranque donde quedo)
      (*PUERTO_B)= (*PUERTO_B) | 0b00100001;
      encendido=1;
    }else{//Si estaba prendido lo apaga
    (*PUERTO_B)= (*PUERTO_B) & 0b11011000;
      encendido=0;
    }
    apretado=1;//Indico que el botón fue apretado 
  }

  if(bit_in!=0 && apretado==1){ //Si deje de pulsar luego de estar pulsando
    for(i=0; i<10000; i++){} 
    apretado=0;
  }
}

void esperar()
{
  volatile long i=0;
  for(i=0; i<12000; i++){
    encender_apagar();//De esta manera verifica constantemente excepto en los instantes de encendido y apagado que son muy pequeños
  }
}