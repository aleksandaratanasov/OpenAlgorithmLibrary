project(OpenAlgorithmLibrary)
cmake_minimum_required(VERSION 2.8)

if(UNIX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x -O1")
    #at the end -O3 (level of optimization 3) and
    #-g0 (no debug information) has to be used
endif()

set(headers
  bubblesort.h
  insertionsort.h
  heapsort.h
  mergesort.h
  quicksort.h
)
set(sources
  main.cpp
)

add_executable(${PROJECT_NAME} ${headers} ${sources})


#NOTES:
# www.stoimen.com/blog/2012/02/13/computer-algorithms-insertion-sort

