cmake_minimum_required(VERSION 3.2)
project(OmpiBenchmarks)

include_directories ("C:/software/openmpi-1.8.1/ompi/include")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu99")

add_executable(OmpiBenchmarks ${SOURCE_FILES} program.h program.c)
