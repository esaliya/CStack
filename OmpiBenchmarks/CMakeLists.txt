cmake_minimum_required(VERSION 3.2)
project(OmpiBenchmarks)

include_directories ("/N/u/sekanaya/buildompi-1.8.1/include")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99")

add_executable(OmpiBenchmarks ${SOURCE_FILES} program.h program.c)
