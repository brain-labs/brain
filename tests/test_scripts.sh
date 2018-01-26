#!/bin/bash

cd $1

$2 test_scripts.c -o test_scripts
if [ $? -ne 0 ] ; then
  echo "Did you pass CLANG as an argument?"
  exit
fi

echo "Luiz Peres" | ./test_scripts

