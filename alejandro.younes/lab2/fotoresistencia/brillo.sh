#!/bin/bash

stty -F /dev/ttyUSB0 speed 2400

cat /dev/ttyUSB0 | while read -n 5 NUM; do
  brightnessctl s $NUM;
done