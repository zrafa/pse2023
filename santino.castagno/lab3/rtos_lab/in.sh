stty -F /dev/ttyACM0 speed 9600
while true; do
    read tecla 
    echo $tecla >>/dev/ttyACM0  
done
