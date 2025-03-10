
read -a array
new_array=()

for ele in "${array[@]}"; do
        if (( ele % 2 == 0 )); then
                new_array+=("$ele")
        fi
done

for ele in "${array[@]}"; do
        if (( ele % 2 != 0 )); then
                new_array+=("$ele")
        fi
done

echo "Original Array: "${array[@]}"
echo "New Array: "${new_array[@]}"
echo "Length of array: ${#array[@]}"
