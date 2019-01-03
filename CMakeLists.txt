cmake_minimum_required(VERSION 3.12)
project(datastructure1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(datastructure1
        AVL.h
        dsexceptions.h
        ImageSystem.cpp
        ImageSystem.h
        library2.cpp
        library2.h
        List.h
        library1List.cpp)


