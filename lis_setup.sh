#!/usr/bin/zsh

num_threads=1
lis_path=./lis/test
binaries_path=./bin

if [[ ! -d lis ]]; then
  wget https://www.ssisc.org/lis/dl/lis-2.1.10.zip
  unzip lis-2.1.10.zip
  mv lis-2.1.10 lis
  echo "directory lis created"
else
  echo "directory lis found"
fi

mpicc -DUSE_MPI -I$mkLisInc -L$mkLisLib -llis $lis_path/test1.c -o $binaries_path/test1

mpirun -n $num_threads $binaries_path/test1 $lis_path/testmat0.mtx $lis_path/testvec0.mtx media/sol.mtx media/hist.txt