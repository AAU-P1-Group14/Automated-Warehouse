#ifndef AUTOMATED_WAREHOUSE_INPUT_MANAGEMENT_H
#define AUTOMATED_WAREHOUSE_INPUT_MANAGEMENT_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../utility/types.h"
#include "array_manager.h"
#include "../utility/misc.h"

void prompt_procedural(bool* procedural);
void select_bench(int* bench);
int input_validation(int height, int width, int layout[height][width], node target);
void input_target(int height, int width, int layout[height][width], node *target);
node random_target(int height, int width, int layout[height][width]);


#endif //AUTOMATED_WAREHOUSE_INPUT_MANAGEMENT_H