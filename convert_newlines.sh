#!/bin/bash

# Loop through all .c files in the current directory
for file in *.c; do
    dos2unix "$file"
done

echo "Newline conversion complete."