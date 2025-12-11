cmake_minimum_required(VERSION 4.0)
project(Automated-Warehouse C)

# Tjek om systemet er Windows
if (WIN32)
    # Kun på Windows: Bag bibliotekerne ind i .exe filen
    set(CMAKE_EXE_LINKER_FLAGS "-static")
endif()

set(CMAKE_C_STANDARD 11)

add_executable(Automated-Warehouse src/main.c
        src/utility/misc.c
        src/algorithms/bfs.c
        src/algorithms/bfs.h
        src/managers/input_manager.c
        src/managers/input_manager.h
        src/managers/array_manager.c
        src/managers/array_manager.h
        src/managers/main_menu.c
        src/managers/main_menu.h
        src/utility/Types.h
        src/algorithms/dfs.c
        src/algorithms/dfs.h
        src/managers/algorithm_manager.c
        src/managers/algorithm_manager.h
        src/algorithms/worst_case.c
        src/algorithms/worst_case.h
        src/dynamic_layout/dynamic_warehouse.c
        src/dynamic_layout/dynamic_warehouse.h)

add_compile_options(-fexec-charset=UTF-8)
