cmake_minimum_required(VERSION 4.0)
project(Automated-Warehouse C)

set(CMAKE_C_STANDARD 11)

add_executable(Automated-Warehouse src/main.c
        src/utility/misc.c
        src/algorithms/bfs.c
        src/algorithms/bfs.h
        src/managers/input_manager.c
        src/managers/input_manager.h
        src/managers/array_manager.c
        src/managers/array_manager.h
        src/utility/Types.h
        src/algorithms/dfs.c
        src/algorithms/dfs.h)
