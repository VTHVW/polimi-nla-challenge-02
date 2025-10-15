cmake_minimum_required(VERSION 3.28)
set(CMAKE_CXX_STANDARD 26)

project(challenge02)

find_package (Eigen3 REQUIRED NO_MODULE) # adding eigen module

# project structure setup
set(dir ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${dir}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${dir}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${dir}/bin")

# first library setup
add_library(matrix_io SHARED include/types.hpp include/matrix_io.hpp src/matrix_io.cpp)
target_include_directories(matrix_io PRIVATE include)
target_link_libraries (matrix_io Eigen3::Eigen)

add_library(matrix_ops SHARED include/types.hpp include/matrix_ops.hpp src/matrix_ops.cpp)
target_include_directories(matrix_ops PRIVATE include)
target_link_libraries (matrix_ops Eigen3::Eigen)

# executables
add_executable(task1 src/task1.cpp)
target_include_directories(task1 PRIVATE include)
target_link_libraries (task1 Eigen3::Eigen matrix_ops matrix_io)

add_executable(task2 src/task2.cpp)
target_include_directories(task2 PRIVATE include)
target_link_libraries (task2 Eigen3::Eigen matrix_ops matrix_io)

# test
add_executable(io_test tests/matrix_io_test.cpp)
target_include_directories(io_test PRIVATE include)
target_link_libraries (io_test Eigen3::Eigen matrix_ops matrix_io)

add_executable(ops_test tests/matrix_ops_test.cpp)
target_include_directories(ops_test PRIVATE include)
target_link_libraries (ops_test Eigen3::Eigen matrix_ops matrix_io)