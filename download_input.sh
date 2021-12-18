#!/bin/sh

echo "THIS CAN'T BE AUTOMATED (PROBABLY)"
exit 1

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <day #>"
    exit
fi

mkdir -p input

for (( i = 1; i<="$1"; i++))
do
    echo "grabbing thing/$i/file.txt"
done
