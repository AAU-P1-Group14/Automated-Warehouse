#ifndef AUTOMATED_WAREHOUSE_INPUT_MANAGEMENT_H
#define AUTOMATED_WAREHOUSE_INPUT_MANAGEMENT_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../utility/types.h"
#include "array_manager.h"
#include "../utility/misc.h"


int input_validation(int layout[HEIGHT][WIDTH], node target);
void input_target(int layout[HEIGHT][WIDTH], node *target_row);
void promptCustomShelf(int layout[HEIGHT][WIDTH], node* target_row);
void random_target(int layout[HEIGHT][WIDTH], node* target);


#endif //AUTOMATED_WAREHOUSE_INPUT_MANAGEMENT_H