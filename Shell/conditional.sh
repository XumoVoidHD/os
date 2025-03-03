#!/bin/bash

echo "Enter a number:"
read num

if [ $num -gt 10 ]; then
    echo "$num is greater than 10."
fi

#!/bin/bash

echo "Enter a number:"
read num

if [ $num -gt 10 ]; then
    echo "$num is greater than 10."
else
    echo "$num is 10 or less."
fi

#!/bin/bash

echo "Enter a number:"
read num

if [ $num -gt 10 ]; then
    echo "$num is greater than 10."
elif [ $num -eq 10 ]; then
    echo "$num is exactly 10."
else
    echo "$num is less than 10."
fi



# Operator	    Meaning
# -eq	        Equal
# -ne	        Not equal
# -gt	        Greater than
# -lt	        Less than
# -ge	        Greater than or equal
# -le	        Less than or equal

