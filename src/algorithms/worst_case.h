
#ifndef AUTOMATED_WORST_CASE_H
#define AUTOMATED_WORST_CASE_H


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../utility/types.h"
#include "../utility/misc.h"


int worst_case(int layout[HEIGHT][WIDTH], node target, node dropoff, node charging, node position);
void move_position(int layout[HEIGHT][WIDTH], node* position, int* tiles);
void update_and_check(int layout[HEIGHT][WIDTH], node target, node dropoff, node charging, node position, int* found_target, int* found_dropoff);
void check_if_target(int layout[HEIGHT][WIDTH], node target, node position, int* found_target);
void check_if_dropoff(int layout[HEIGHT][WIDTH], node dropoff, node position, int* found_dropoff);


#endif //AUTOMATED_WORST_CASE_H




