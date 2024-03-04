#!/bin/bash

gcc -c -fPIC -lm invsqrt.c
gcc -c -fPIC -O3 -ffast-math -lm opt_invsqrt.c
gcc invsqrt.o opt_invsqrt.o -shared -o lib_invsqrt.so

gcc main.c -L . -l_invsqrt -lm -o main

# export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:."
