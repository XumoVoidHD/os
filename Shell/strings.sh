# String Comparisons:
# Operator	    Meaning
# ==	        Equal
# !=	        Not equal
# -z str	    String is empty
# -n str	    String is not empty

#!/bin/bash

echo "Enter a word:"
read word

if [[ "$word" == "hello" ]]; then
    echo "You entered hello!"
else
    echo "You did not enter hello."
fi



#!/bin/bash

echo -n "Enter a character: "
read -n 1 char  # Reads only one character
echo
echo "You entered: $char"



#!/bin/bash

echo -n "Enter your name: "
read name

if [ "$name" == "Alice" ]; then
    echo "Hello, Alice!"
else
    echo "You are not Alice."
fi



#!/bin/bash

echo -n "Enter a word: "
read word

length=${#word}
echo "The length of '$word' is $length characters."



#!/bin/bash

string="Hello, World!"
echo "Substring (starting from index 7, length 5): ${string:7:5}"



#!/bin/bash

echo -n "Enter a string: "
read str

last_char="${str: -1}"  # Extract last character
echo "Last character: $last_char"



#!/bin/bash

str="Welcome to Bash scripting!"
substring="Bash"

if [[ "$str" == *"$substring"* ]]; then
    echo "Substring found!"
else
    echo "Substring not found!"
fi
