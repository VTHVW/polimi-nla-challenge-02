#!/bin/bash
cmake -S  ./ -B ./build
make -C build/
./bin/$1