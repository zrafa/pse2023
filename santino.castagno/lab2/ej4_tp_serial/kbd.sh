stty -F /dev/ttyUSB0 speed 9600
while true; do
    read -n 1 tecla 
    echo $tecla >>/dev/ttyUSB0  
done
