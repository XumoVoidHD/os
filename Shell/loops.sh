#!/bin/bash

for i in {1..5}; do
    echo "Iteration: $i"
done


#!/bin/bash

for ((i = 1; i <= 5; i++)); do
    echo "Iteration: $i"
done

#!/bin/bash

count=1
while [ $count -le 5 ]; do
    echo "Count: $count"
    ((count++))
done


#!/bin/bash

count=1
until [ $count -gt 5 ]; do
    echo "Count: $count"
    ((count++))
done



#!/bin/bash

while true; do
    echo "Infinite loop! Press CTRL+C to stop."
    sleep 1
done
