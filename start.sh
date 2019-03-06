#!/bin/bash

./build.sh

./build/src/Image_Grabber/Image_Grabber &
./build/src/ECU_Communication/ECU_Communication & 