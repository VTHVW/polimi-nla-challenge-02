#!/bin/bash

export num_threads=4  # default threads to use if mpi is enabled
export lis_path=./lis/test # path to location of files to compile
export lis_output_dir=./media/lisres # path for lis output
export binaries_path=./bin # path of compilation results
export lis_compiler="gcc"  # generic compiler to use
export lis_exec_prefix=""  # generic options to use when executing (mostly for mpi)

# args initialization
for arg in "$@"; do
  shift
  case "$arg" in
    "--help")     set -- "$@" "-h" ;;
    "--verbose")  set -- "$@" "-v" ;;
    "--threads")       set -- "$@" "-n" ;;
    "--test")       set -- "$@" "-t" ;;
    *)              set -- "$@" "$arg" ;;
  esac
done

while getopts "hvtn:" opt; do
  case "$opt" in
    "v")
      verbose=true ;;
    "t")
      do_tests=true ;;
    "n")
      if [[ -z "$OPTARG" || "${OPTARG:0:1}" = "-" ]] ; then
        exit 1
      fi
      num_threads=$OPTARG ;;
    "h")
      echo -e "USAGE: \x1b[1m$0\x1b[0m [PARAMS]"
      echo -e "PARAMS:"
      echo -e "\t--help,      -h\tshow this text"
      echo -e "\t--verbose,   -v\tenable printing of debug info"
      echo -e "\t--threads N, -n N\tset numbers of threads if mpi is enabled"
      echo -e "\t--test,      -t\ttest compiled files"
      exit 0 ;;
    \?)
      echo "Invalid option: please use --help for more info on how to use." >&2
      exit 1;;
    :)
      echo "Argument required:  please use --help for more info on how to use." >&2
      exit 1;;
    *) ;;
  esac
done

if [[ $APPTAINER_NAME ]]; then

  if [[ $verbose ]]; then echo "In AppTainer: using mpicc and mpirun"; fi

  lis_compiler="mpicc -DUSE_MPI"
  lis_exec_prefix="mpirun -n $num_threads"
else

  if [[ $verbose ]]; then echo "Not in AppTainer: using gcc"; fi

  lis_compiler="gcc"
  lis_exec_prefix=""
fi

# if lis dir not present download it and unzip
if [[ ! -d lis ]]; then
  if [[ $verbose ]]; then echo "Directory lis not found, downloading from https://www.ssisc.org/lis/dl/lis-2.1.10.zip"; fi
  wget --quiet https://www.ssisc.org/lis/dl/lis-2.1.10.zip
  wget_res=$?
  if [[ ! wget_res -eq 0 ]]; then echo "Couldn't download lis directory... Aborting." >&2 ; exit $wget_res; fi
  unzip lis-2.1.10.zip
  mv lis-2.1.10 lis
  if [[ $verbose ]]; then echo "Directory lis created"; fi
else
  if [[ $verbose ]]; then echo "Directory lis found"; fi
fi


$lis_compiler $lis_path/etest1.c -I$mkLisInc -L$mkLisLib -llis -lm -o $binaries_path/lis_eigensolver1
comp_res=$?
if [[ ! comp_res -eq 0 ]]; then
  echo "Couldn't compile $lis_path/etest1.c into $binaries_path/lis_eigensolver1... Aborting." >&2
  exit $comp_res
fi
if [[ $verbose ]]; then echo "$binaries_path/lis_eigensolver1 compiled"; fi

$lis_compiler $lis_path/etest2.c -I$mkLisInc -L$mkLisLib -llis -lm -o $binaries_path/lis_eigensolver2
comp_res=$?
if [[ ! comp_res -eq 0 ]]; then
  echo "Couldn't compile $lis_path/etest2.c into $binaries_path/lis_eigensolver2... Aborting." >&2
  exit $comp_res
fi
if [[ $verbose ]]; then echo "$binaries_path/lis_eigensolver2 compiled"; fi

$lis_compiler $lis_path/etest4.c -I$mkLisInc -L$mkLisLib -llis -lm -o $binaries_path/lis_eigensolver4
comp_res=$?
if [[ ! comp_res -eq 0 ]]; then
  echo "Couldn't compile $lis_path/etest4.c into $binaries_path/lis_eigensolver4... Aborting." >&2
  exit $comp_res
fi
if [[ $verbose ]]; then echo "$binaries_path/lis_eigensolver4 compiled"; fi

$lis_compiler $lis_path/etest5.c -I$mkLisInc -L$mkLisLib -llis -lm -o $binaries_path/lis_eigensolver5
comp_res=$?
if [[ ! comp_res -eq 0 ]]; then
  echo "Couldn't compile $lis_path/etest5.c into $binaries_path/lis_eigensolver5... Aborting." >&2
  exit $comp_res
fi
if [[ $verbose ]]; then echo "$binaries_path/lis_eigensolver4 compiled"; fi

if [[ $do_tests ]]; then
  if [[ $verbose ]]; then echo "Running tests..."; fi
  $lis_exec_prefix $binaries_path/lis_eigensolver1 $lis_path/testmat0.mtx $lis_path/eigvec.txt $lis_output_dir/.test1_hist.txt -e pi &> $lis_output_dir/.test1_out.txt
  $lis_exec_prefix $binaries_path/lis_eigensolver2 20 20 1 $lis_output_dir/.test2_eigvec.mtx $lis_output_dir/.test2_hist.txt &> $lis_output_dir/.test2_out.txt
  $lis_exec_prefix $binaries_path/lis_eigensolver4 100 &> $lis_output_dir/.test4_out.txt
  $lis_exec_prefix $binaries_path/lis_eigensolver5 $lis_path/testmat0.mtx  $lis_path/evals.mtx $lis_output_dir/.test5_eigvecs.mtx $lis_output_dir/.test5_res.txt $lis_output_dir/.test5_iters.txt -ss 4 -e li &> $lis_output_dir/.test5_out.txt
  if [[ $verbose ]]; then echo "Done testing, please check everything works as expected with $lis_output_dir/.testX_out.txt"; fi
fi