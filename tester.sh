#!/bin/bash

for ((X=1; X<=19; X++))
do
    filename="bad${X}.cub"
    echo "Running cub3d with ${filename}"
    ./cub3d assets/maps/"${filename}"
done
