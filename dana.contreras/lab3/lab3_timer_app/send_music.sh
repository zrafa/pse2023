#!/bin/bash

music_file="cancion.mp3.wav"
port="/dev/ttyUSB0"

stty -F "$port" speed 115200

cat $music_file > $port
#ffmpeg  -f pulse -i default  -ar 11000 -acodec pcm_u8 -ac 1 -f wav pipe:1 | cat > $port
