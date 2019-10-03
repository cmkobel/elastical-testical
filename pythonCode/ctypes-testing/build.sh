#!/bin/bash


gcc -shared -Wl,-soname,hmmlib -o hmmlib.so -fPIC hmmlib.c

