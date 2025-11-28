#ifndef AUTOMATED_WAREHOUSE_ARRAYMANAGEMENT_H
#define AUTOMATED_WAREHOUSE_ARRAYMANAGEMENT_H

#include <stdbool.h>
#include <stdio.h>
#include "../utility/types.h"

void init_array(int height, int width, int layout[height][width]); // prototype of initArray
void print_array(int height, int width, int layout[height][width], bool print_num); // prototype of printArray
void clear_path(int *height, int *width, int layout[*height][*width], node path[*height * *width], int* tiles, node target_t);
void force_clear_path(int *height, int *width, int layout[*height][*width]);

#endif //AUTOMATED_WAREHOUSE_ARRAYMANAGEMENT_H