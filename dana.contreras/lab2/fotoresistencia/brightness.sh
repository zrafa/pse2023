stty -F /dev/ttyUSB0 speed 2400 raw
sudo cat /dev/ttyUSB0 | while read -d "-" range;
do
    brightnessctl s $(expr $range + 0);
done