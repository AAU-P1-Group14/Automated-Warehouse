
#ifndef AUTOMATED_WORST_CASE_H
#define AUTOMATED_WORST_CASE_H


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../utility/types.h"
#include "../utility/misc.h"


int worst_case(int *height, int *width, int layout[*height][*width], node target, node dropoff, node charging, node position);
void move_position(int *height, int *width, int layout[*height][*width], node* position, int* tiles);
void update_and_check(int *height, int *width, int layout[*height][*width], node target, node dropoff, node charging, node position, int* found_target, int* found_dropoff);
void check_for_adjecent(int *height, int *width, int layout[*height][*width], node check_cell, node position, int* boolean_argument);


#endif //AUTOMATED_WORST_CASE_H




