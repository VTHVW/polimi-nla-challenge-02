cmake_minimum_required(VERSION 3.28)
set(CMAKE_CXX_STANDARD 26)

project(challenge02)

# project structure setup
set(dir ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${dir}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${dir}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${dir}/bin")
set(my_libs "matrix_io matrix_ops")

# first library setup
add_library(matrix_io SHARED include/types_and_defs.hpp include/matrix_io.hpp src/matrix_io.cpp)
target_link_libraries (matrix_io Eigen3::Eigen)
add_library(matrix_ops SHARED include/types_and_defs.hpp include/matrix_ops.hpp src/matrix_ops.cpp)
target_link_libraries (matrix_ops Eigen3::Eigen)

add_executable(task1 src/task1.cpp)
find_package (Eigen3 REQUIRED NO_MODULE)
target_include_directories(task1 PRIVATE include)
target_link_libraries (task1 Eigen3::Eigen $my_libs)