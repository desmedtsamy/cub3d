#!/bin/bash

for ((X=1; X<=23; X++))
do
    filename="bad${X}.cub"
    echo "Running cub3d with ${filename}"
    ./cub3d assets/maps/bad/"${filename}"
done
