cmake_minimum_required(VERSION 3.27)
project(homework_3)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(homework_3
        IGraph.h
        ListGraph.cpp
        ListGraph.h
        MatrixGraph.cpp
        MatrixGraph.h
        ArcGraph.cpp
        SetGraph.cpp
        main.cpp
)
