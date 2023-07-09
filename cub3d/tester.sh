#!/bin/bash


echo "Running cub3d with prout"
./cub3d assets/maps/prout
for ((X=1; X<=27; X++))
do
    filename="bad${X}.cub"
    echo "Running cub3d with ${filename}"
    ./cub3d assets/maps/bad/"${filename}"
done
