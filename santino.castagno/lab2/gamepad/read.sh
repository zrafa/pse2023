stty -F /dev/ttyACM0 speed 9600
cat /dev/ttyACM0 |
while read tecla; do
    echo asd
    echo $tecla                # muestra la letra de la pulsación en pantalla
done
