#!/usr/bin/bash

export num_threads=4  # default threads to use if mpi is enabled
export lis_output_dir=./media/lisres # path for lis output
export lis_input_dir=./media/matrices # path for lis output
export binaries_path=./bin # path of compilation results
export lis_compiler="gcc"  # generic compiler to use
export lis_exec_prefix=""  # generic options to use when executing (mostly for mpi)
export es1=$binaries_path/lis_eigensolver1
export es5=$binaries_path/lis_eigensolver5
export max_iter=3000
export shift=29.5

# args initialization
for arg in "$@"; do
  shift
  case "$arg" in
    "--help")     set -- "$@" "-h" ;;
    "--verbose")  set -- "$@" "-v" ;;
    "--threads")       set -- "$@" "-n" ;;
    "--maxiter")    set -- "$@" "-m" ;;
    "--shift")      set -- "$@" "-s" ;;
    *)              set -- "$@" "$arg" ;;
  esac
done

while getopts "hvn:m:s:" opt; do
  case "$opt" in
    "v")
      verbose=true ;;
    "n")
      if [[ -z "$OPTARG" || "${OPTARG:0:1}" = "-" ]] ; then
        exit 1
      fi
      num_threads=$OPTARG ;;
    "m")
      if [[ -z "$OPTARG" || "${OPTARG:0:1}" = "-" ]] ; then
        exit 1
      fi
      max_iter=$OPTARG ;;
    "s")
      if [[ -z "$OPTARG" || "${OPTARG:0:1}" = "-" ]] ; then
        exit 1
      fi
      shift=$OPTARG ;;
    "h")
      echo -e "USAGE: \x1b[1m$0\x1b[0m [PARAMS]"
      echo -e "PARAMS:"
      echo -e "\t--help,      -h\tshow this text"
      echo -e "\t--verbose,   -v\tenable printing of debug info"
      echo -e "\t--threads N, -n N\tset numbers of threads if mpi is enabled"
      echo -e "\t--maxiter M, -m M\tset maximum number of iteration for the eigensolver to M"
      echo -e "\t--shift S, -s S\tset shift mu for the eigensolver to S"
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
if [[ ! $verbose ]]; then
  ./lis_setup.sh -n $num_threads
else
  ./lis_setup.sh -n $num_threads -v
fi

if [[ $? != 0 ]]; then
  echo "Error during setup" >&2
  exit 1
fi

if [[ $APPTAINER_NAME ]]; then
  if [[ $verbose ]]; then echo "In AppTainer: using mpicc and mpirun"; fi
  lis_compiler="mpicc -DUSE_MPI"
  lis_exec_prefix="mpirun -n $num_threads"
else
  if [[ $verbose ]]; then echo "Not in AppTainer: using gcc"; fi
  lis_compiler="gcc"
  lis_exec_prefix=""
fi

if [[ $verbose ]]; then echo "Computing largest eigen value and eigenvector (max iteration: $max_iter):"; fi

# the largest eigenvalue of L_s up to a tolerance of 10^8
if [[ $verbose ]]; then
  $lis_exec_prefix $es1  $lis_input_dir/social_laplacian.mtx $lis_output_dir/task3_evec_larger.mtx $lis_output_dir/task3_hist_larger.txt -e pi -etol 1.0e-8 -p ilut -emaxiter $max_iter
else
  $lis_exec_prefix $es1  $lis_input_dir/social_laplacian.mtx $lis_output_dir/task3_evec_larger.mtx $lis_output_dir/task3_hist_larger.txt -e pi -etol 1.0e-8 -p ilut -emaxiter $max_iter &> $lis_output_dir/task3_output_larger.txt
fi

if [[ $? != 0 ]]; then
  echo "Error during eigenvalue calculation" >&2
  exit 1
fi


if [[ $verbose ]]; then echo "Computing largest eigen value and eigenvector (max iteration: $max_iter, μ: $shift):"; fi

# Find a shift μ yielding an acceleration of the previous eigensolver
if [[ $verbose ]]; then
  $lis_exec_prefix $es1  $lis_input_dir/social_laplacian.mtx $lis_output_dir/task3_evec_shift.mtx $lis_output_dir/task3_hist_shift.txt -e ii -etol 1.0e-8 -p iluc -emaxiter $max_iter -shift $shift
else
  $lis_exec_prefix $es1  $lis_input_dir/social_laplacian.mtx $lis_output_dir/task3_evec_shift.mtx $lis_output_dir/task3_hist_shift.txt -e ii -etol 1.0e-8 -p iluc -emaxiter $max_iter -shift $shift &> $lis_output_dir/task3_output_shift.txt
fi

if [[ $? != 0 ]]; then
  echo "Error during shift calculation" >&2
  exit 1
fi

if [[ $verbose ]]; then echo "Computing second smallest eigen value and eigenvector (max iteration: $max_iter):"; fi

if [[ $verbose ]]; then
  $lis_exec_prefix $es5 $lis_input_dir/social_laplacian.mtx $lis_output_dir/task3_evals_second_smallest.mtx \
   $lis_output_dir/task3_evecs_second_smallest.mtx $lis_output_dir/task3_hist_second_smallest.txt $lis_output_dir/task3_iter_second_smallest.txt \
   -e si -etol 1.0e-10 -i cg -p ilut -emaxiter $max_iter -ss 2
else
  $lis_exec_prefix $es5 $lis_input_dir/social_laplacian.mtx $lis_output_dir/task3_evals_second_smallest.mtx \
   $lis_output_dir/task3_evecs_second_smallest.mtx $lis_output_dir/task3_hist_second_smallest.txt $lis_output_dir/task3_iter_second_smallest.txt \
   -e si -etol 1.0e-10 -i cg -p ilut -emaxiter $max_iter -ss 2 &> $lis_output_dir/task3_output_second_smallest.txt
fi

if [[ $? != 0 ]]; then
  echo "Error during second smallest eval calculation" >&2
  exit 1
fi
