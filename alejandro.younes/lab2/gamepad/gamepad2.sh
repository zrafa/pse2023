#!/bin/bash

stty -F /dev/ttyUSB0 speed 2400

dispara=false
cat /dev/ttyUSB0 | while read -n 1 tecla; do
    if [[ "$tecla" == "s" ]]; then
        if [[ dispara == false ]]; then
            xdotool keydown space;
            dispara=true;
        else
            xdotool keyup space;
            dispara=false;
        fi
    fi
    if [[ "$tecla" == "?" ]]; then
        xdotool keydown Left;
        xdotool keydown Right;
    elif [[ "$tecla" == "a" ]]; then
        xdotool keydown Left;
        xdotool keyup Right;
    elif [[ "$tecla" == "d" ]]; then
        xdotool keydown Right;
        xdotool keyup Left;
    fi
done
