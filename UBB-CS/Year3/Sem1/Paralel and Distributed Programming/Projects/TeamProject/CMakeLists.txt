cmake_minimum_required(VERSION 3.27)
project(TeamProject)

set(CMAKE_CXX_STANDARD 17)

# Set the MPI_CXX_COMPILER to the path of the mpiexec executable
set(MPI_CXX_COMPILER "C:/Program Files/Microsoft MPI/Bin/mpiexec.exe")

# Find MPI package and include its directories
find_package(MPI REQUIRED)
include_directories(${MPI_INCLUDE_PATH})

# Add your source files
add_executable(TeamProject main.cpp)

# Link MPI libraries
target_link_libraries(TeamProject PRIVATE ${MPI_CXX_LIBRARIES})
