cmake_minimum_required(VERSION 4.0)
project(Automated-Warehouse C)

set(CMAKE_C_STANDARD 11)

add_executable(Automated-Warehouse main.c
        main.c
        funcs.c
        BFS.c
        BFS.h
        input_management.c
        input_management.h
        arrayManagement.c
        arrayManagement.h
        types.h)
