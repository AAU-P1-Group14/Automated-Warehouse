#ifndef AUTOMATED_WAREHOUSE_INPUT_MANAGEMENT_H
#define AUTOMATED_WAREHOUSE_INPUT_MANAGEMENT_H

#include <stdio.h>
#include "../utility/types.h"


int input_validation(int layout[HEIGHT][WIDTH], int target_row, int target_col);
void input_target(int layout[HEIGHT][WIDTH], int* target_row, int* target_col);
void promptCustomShelf(int layout[HEIGHT][WIDTH], int* target_row, int* target_col);


#endif //AUTOMATED_WAREHOUSE_INPUT_MANAGEMENT_H