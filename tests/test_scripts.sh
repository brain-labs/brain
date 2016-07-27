#!/bin/bash

cd $1

clang test_scripts.c -o test_scripts

echo "Luiz Peres" | ./test_scripts
 
