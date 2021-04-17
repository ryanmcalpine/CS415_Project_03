cmake_minimum_required(VERSION 3.17)
project(CS415_Project_03)

set(CMAKE_CXX_STANDARD 14)

include_directories(bst)

add_executable(CS415_Project_03
        bst/bst.cpp
        bst/bst.h
        bst/main.cpp bst/TwoThreeTree.cpp bst/TwoThreeTree.h)
