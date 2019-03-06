#!/bin/bash

./build.sh


workon cv
python ./src/Image_Grabber_py/main.py &
./build/src/ECU_Communication/ECU_Communication & 