#!/bin/bash
cmake -S  ./ -B ./build
make -C build/

if [[ $1 = "all" ]]; then
  for i in `ls ./bin/*task*`; do
    $i
    echo "$i done: $?"
  done
elif [[ $1 = "test" ]]; then
  for i in `ls ./bin/*test*`; do
    $i
    echo "$i done: $?"
  done
elif [[ $1 = "docs" ]]; then
  doxygen ./docs/Doxyfile
  make -C ./docs/latex
else
  ./bin/$1
fi