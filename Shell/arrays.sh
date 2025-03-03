#!/bin/bash

fruits=("Apple" "Banana" "Cherry")

echo "First fruit: ${fruits[0]}"
echo "All fruits: ${fruits[@]}"



#!/bin/bash

fruits=("Apple" "Banana" "Cherry")

for fruit in "${fruits[@]}"; do
    echo "Fruit: $fruit"
done



#!/bin/bash

fruits=("Apple" "Banana" "Cherry")

for i in "${!fruits[@]}"; do
    echo "Index $i: ${fruits[$i]}"
done
