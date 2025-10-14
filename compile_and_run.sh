#!/bin/bash
cmake -S  ./ -B ./build
make -C build/

if [[ ! $1 = "all" ]]; then
  ./bin/$1
else
  for i in `ls ./bin/`; do
    ./bin/$i
    done
fi