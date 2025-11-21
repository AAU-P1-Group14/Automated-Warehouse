#ifndef AUTOMATED_WAREHOUSE_ARRAYMANAGEMENT_H
#define AUTOMATED_WAREHOUSE_ARRAYMANAGEMENT_H

#include <stdbool.h>
#include <stdio.h>
#include "../utility/types.h"

void init_array(int layout[HEIGHT][WIDTH]); // prototype of initArray
void print_array(int layout[HEIGHT][WIDTH], bool print_num); // prototype of printArray
void clear_path(int layout[HEIGHT][WIDTH], node path[HEIGHT * WIDTH], int* tiles, node target_t);

#endif //AUTOMATED_WAREHOUSE_ARRAYMANAGEMENT_H