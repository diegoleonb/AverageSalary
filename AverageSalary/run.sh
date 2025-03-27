#!/bin/bash

SOURCE_DIR=$(pwd)

OUTPUT_DIR="$SOURCE_DIR/bin"

OUTPUT_NAME="AverageSalary"

if [ ! -f "$OUTPUT_DIR/$OUTPUT_NAME" ]; then
    echo "Error: Compile first."
    exit 1
fi

if [ $# -eq 0 ]; then
    echo "Error: No file."
    echo "./run.sh <file>"
    exit 1
fi

INPUT_FILE="$1"

if [ ! -f "$INPUT_FILE" ]; then
    echo "Error: File doesn't exist."
    exit 1
fi

"$OUTPUT_DIR/$OUTPUT_NAME" "$INPUT_FILE"
