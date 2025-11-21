#ifndef AUTOMATED_WAREHOUSE_WORST_CASE_H
#define AUTOMATED_WAREHOUSE_WORST_CASE_H

#include <stdio.h>
#include "../utility/types.h"

int worst_case(int layout[HEIGHT][WIDTH], node target, node start);
void update_and_check(int layout[HEIGHT][WIDTH], node target, node position, int* found_target, int* found_dropoff);
void check_if_target(int layout[HEIGHT][WIDTH], node target, node position, int* found_target);
void check_if_dropoff(int layout[HEIGHT][WIDTH], node target, node position, int* found_dropoff);

#endif //AUTOMATED_WAREHOUSE_WORST_CASE_H