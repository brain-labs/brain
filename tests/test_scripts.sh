#!/bin/bash

cd $1

clang-3.8 test_scripts.c -o test_scripts

echo "Luiz Peres" | ./test_scripts

