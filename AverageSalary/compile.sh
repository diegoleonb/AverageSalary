#!/bin/bash

SOURCE_DIR=$(pwd)
OUTPUT_DIR="$SOURCE_DIR/bin"

OUTPUT_NAME="AverageSalary" 

mkdir -p "$OUTPUT_DIR"

echo "Build started..."
g++ "$SOURCE_DIR/AverageSalary.cpp" -o "$OUTPUT_DIR/$OUTPUT_NAME"

if [[ $? -ne 0 ]]; then
    echo "Error."
    exit 1
else
    echo "Build completed."
fi
