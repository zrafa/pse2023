stty -F /dev/ttyUSB0 speed 2400 # establece la velocidad del puerto serial
while true; do
  read -n 1 tecla # espera por una pulsación del teclado, almacena el valor en 'tecla'
  echo $tecla # muestra la letra de la pulsación en pantalla
  echo $tecla >> /dev/ttyUSB0 # envía el contenido de 'tecla' al driver del dispositivo serial, quien a su vez lo envía por el hardware al MCU del otro lado
done