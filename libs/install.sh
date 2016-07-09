#!/bin/bash

echo "Creating libraries..."

inc_path=/usr/local/include/brain

mkdir -p $inc_path
if [ $? -ne 0 ] ; then
  exit  
fi

files=$(find $1 -type f -name "*.c")
if [ $? -ne 0 ] ; then
  echo "Please pass an argument like '.' or '../libs/'"
  exit
fi

for lib in $files 
do
  filename=$(basename "$lib")
  filename="${filename%.*}"
  clang-3.8 -S -emit-llvm $lib -o $inc_path/$filename.ll  
  if [ $? -ne 0 ] ; then
    exit
  else
    echo "Library '$inc_path/$filename' done....."
  fi
done

echo 'That was not so bad, eh?!'
