cmake_minimum_required(VERSION 4.0)
project(Automated-Warehouse C)

set(CMAKE_C_STANDARD 11)

add_executable(Automated-Warehouse src/Main.c
        src/Main.c
        src/utility/Misc.c
        src/algorithms/BFS.c
        src/algorithms/BFS.h
        src/managers/input_manager.c
        src/managers/input_manager.h
        src/managers/array_manager.c
        src/managers/array_manager.h
        src/utility/Types.h)
