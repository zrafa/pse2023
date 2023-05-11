stty -F /dev/ttyACM0 speed 9600
brightnessctl m
cat /dev/ttyACM0 |
while read value; do
    brightnessctl s $value%;
done
