project(OpenAlgorithmLibrary)
cmake_minimum_required(VERSION 2.8)

if(UNIX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x -O3") #-g0")
    #-O3 (level of optimization 3)
    #-g0 (no debug information)
    #disable all output by commenting out #define OUTPUT
endif()

set(headers
  bubblesort.h
  insertionsort.h
  heapsort.h
  mergesort.h
  quicksort.h
  shellsort.h
  swap.h
  randomstring.h
)
set(sources
  main.cpp
  randomstring.cpp
)

add_executable(${PROJECT_NAME} ${headers} ${sources})

#NOTES:
# http://algs4.cs.princeton.edu/23quicksort/
