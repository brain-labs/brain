#!/bin/bash

echo $1
export BRAIN_LIB=/usr/local/include/brain
export PATH=$PATH:$1/bin
