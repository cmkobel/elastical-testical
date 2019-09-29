#!/bin/bash

mkdir -p hmmmlib/build && cd hmmmlib/build/ && cmake .. && make && python ../../pythonCode/binding.py; cd ../../

