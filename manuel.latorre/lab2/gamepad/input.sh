#!/bin/bash
stty -F /dev/ttyUSB0 speed 2400 # establecer la velocidad de la conexión serial
sudo cat /dev/ttyUSB0 | while read -n 1 tecla; do
    if [ "$tecla" == "a" ]; then 
        xdotool keydown "a"
    elif [ "$tecla" == "d" ]; then   
        xdotool keydown "d"
    elif [ "$tecla" == "s" ]; then 
        xdotool keyup "a" 
        xdotool keyup "d"
    elif [ "$tecla" == "b" ]; then 
        xdotool keydown "b"
    elif [ "$tecla" == "q" ]; then
        xdotool keyup "b"
    fi
done 