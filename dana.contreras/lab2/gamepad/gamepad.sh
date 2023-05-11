stty -F /dev/ttyUSB0 speed 2400 min 100 time 2 -icrnl -imaxbel -opost -onlcr -isig -icanon -echo brkint
xdg-open 'https://www.playdosgames.com/play/tyrian/'
stdbuf -o0 cat /dev/ttyUSB0 | while read -n 1 key_char; do
    case $key_char in
    'a') (xdotool keyup Right keydown --delay 12 Left);;
    'd') (xdotool keyup Left keydown --delay 12 Right) ;;
    's') (xdotool keyup Right keyup Left key --repeat 20 --delay 12 Down);;
    'b') (xdotool key --repeat 7 --delay 24 space);;
    esac
done