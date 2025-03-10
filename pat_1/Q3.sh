#!/bin/bash

for ((i = 1; i <= 3; i++)); do
    # Take input
    echo -n "Enter x coordinate: "
    read x
    echo -n "Enter y coordinate: "
    read y

    # Determine quadrant or axis
    if [[ $x -eq 0 && $y -eq 0 ]]; then
        echo "Point lies at the origin."
    elif [[ $x -eq 0 || $y -eq 0 ]]; then
        echo "Point lies on an axis."
    elif [[ $x -gt 0 && $y -gt 0 ]]; then
        echo "Point lies in Quadrant I."
    elif [[ $x -lt 0 && $y -gt 0 ]]; then
        echo "Point lies in Quadrant II."
    elif [[ $x -lt 0 && $y -lt 0 ]]; then
        echo "Point lies in Quadrant III."
    else
        echo "Point lies in Quadrant IV."
    fi

    # Determine shape and print pattern
    if [[ $x -eq 0 && $y -eq 0 ]]; then
        echo "Shape: Dot"
        echo "*"
    elif [[ $x -eq 0 ]]; then
        echo "Shape: Vertical Line"
        for ((j = 0; j < y; j++)); do
            echo "*"
        done
    elif [[ $y -eq 0 ]]; then
        echo "Shape: Horizontal Line"
        for ((j = 0; j < x; j++)); do
            echo -n "*"
        done
        echo
    else
        echo "Shape: Rectangle"
        for ((j = 0; j < y; j++)); do
            for ((k = 0; k < x; k++)); do
                echo -n "* "
            done
            echo
        done
    fi

    echo "----------------------"
done
