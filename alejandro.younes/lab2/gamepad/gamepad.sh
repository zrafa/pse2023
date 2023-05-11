#!/bin/bash

stty -F /dev/ttyUSB0 speed 2400

cat /dev/ttyUSB0 | while read -n 1 tecla; do
    if [[ "$tecla" == "s" ]]; then
        xdotool key space;
    fi
    if [[ "$tecla" == "a" ]]; then
        xdotool key Left;
    elif [[ "$tecla" == "d" ]]; then
        xdotool key Right;
    fi
done
