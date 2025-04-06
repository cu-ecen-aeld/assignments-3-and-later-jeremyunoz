#!/bin/bash

if [ $# -ne 2 ]; then
    echo "Error: Two arguments required."
    echo "Usage: $0 <full_file_path> <text_to_write>"
    exit 1
fi

writefile="$1"
writestr="$2"

dir_path=$(dirname "$writefile")

mkdir -p "$dir_path"

echo "$writestr" > "$writefile"

if [ $? -ne 0 ]; then
    echo "Error: Could not create or write to file '$writefile'"
    exit 1
fi

echo "File '$writefile' successfully created with content: '$writestr'"
