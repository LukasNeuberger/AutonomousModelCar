#!/bin/bash

./compile.sh

trap "exit" INT TERM ERR
trap "kill 0" EXIT

declare -a arr=("ECU_Communication" "Image_Grabber")
for i in "${arr[@]}"
do
   ./build/src/${i}/${i} | tee ${i}.log | sed -e "s/^/[${i}] /" &
done

wait