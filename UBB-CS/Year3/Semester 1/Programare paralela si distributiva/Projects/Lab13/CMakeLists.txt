cmake_minimum_required(VERSION 3.27)
project(Lab13)

set(CMAKE_CXX_STANDARD 17)
set(MPI_CXX_COMPILER "mpiexec")

find_package(MPI REQUIRED)
include_directories(${MPI_INCLUDE_PATH})
add_executable(Lab13 main.cpp)
target_link_libraries(Lab13 PRIVATE ${MPI_CXX_LIBRARIES})