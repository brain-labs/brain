#!/bin/bash

cd $1

clang test_scripts.c -o test_scripts

./test_scripts
