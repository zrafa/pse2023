#!/bin/bash

music_file="lets_groove.raw"
port="/dev/ttyUSB0"

stty -F "$port" speed 2400

cat /dev/ttyUSB0 | while IFS= read -r -n1 byte; do
    echo -n "$byte" > "$port"
done < <(od -An -v -t u1 -w1 "$music_file")
