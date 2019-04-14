#!/bin/bash
set -e

./generate_message_types.sh
./compile.sh

mkdir -p logs

trap "exit" INT TERM ERR
trap "kill 0" EXIT

declare -a arr=("ECU_Communication" "Image_Grabber")
for i in "${arr[@]}"
do
   ./bin/${i} | tee ./logs/${i}.log | sed -e "s/^/[${i}] /" &
done

wait