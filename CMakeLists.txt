cmake_Minimum_required(VERSION 3.9)
project(mevni3Wet2)

set(CMAKE_CXX_STANDARD 11)

add_executable(mevni3Wet2 main.cpp Image.cpp Image.h Labels.h Union-Find.h
        AVLtree.h exceptions.h MaxHeap.h library.h ChainHashing.h List.h Ds.cpp
        Ds.h library.cpp)