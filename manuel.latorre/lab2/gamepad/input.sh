#!/bin/bash
is_pressed_a=false
is_pressed_d=false
is_pressed_b=false
stty -F /dev/ttyUSB0 speed 2400 # establecer la velocidad de la conexión serial
sudo cat /dev/ttyUSB0 | while read -n 1 tecla; do
    if [ "$tecla" == "a" ]; then #Control desplazamiento desp_izq
      if ! $is_pressed_a; then
        is_pressed_a=true
        is_pressed_b=false
        is_pressed_a=false
        xdotool keyup "d"
        xdotool keyup --clearmodifiers "b" 
        xdotool keydown "a"
        
      fi
    elif [ "$tecla" == "d" ]; then #Control desp_der
      if ! $is_pressed_d; then
        is_pressed_d=true   
        is_pressed_b=false
        is_pressed_a=false
        xdotool keyup "a"
        xdotool keyup --clearmodifiers "b" 
        xdotool keydown "d"
        
      fi
    elif [ "$tecla" == "b" ]; then #Control disparo quieto
      if ! $is_pressed_b; then
        is_pressed_b=true   
        xdotool keydown "b"
      fi
    elif [ "$tecla" == "l" ]; then #Control disparo+desp_izq
        is_pressed_b=true   
        is_pressed_a=true
        is_pressed_d=false
        xdotool keyup "d"
        xdotool keydown "b" keydown "a" 
    elif [ "$tecla" == "r" ]; then #Control disparo+desp_der
        is_pressed_b=true   
        is_pressed_d=true
        is_pressed_a=false 
        xdotool keyup "a"
        xdotool keydown "d" keydown "b"
    elif [[ "$tecla" == "q" ]]; then #Control disparo soltado
      is_pressed_b=false 
      xdotool keyup --clearmodifiers "b" 
    elif [[ "$tecla" == "s" ]]; then #Control detener
        is_pressed_a=false  
        is_pressed_d=false 
        is_pressed_b=false 
        xdotool keyup "a"
        xdotool keyup "d"
        xdotool keyup "b"

    fi
done