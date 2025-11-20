#ifndef AUTOMATED_WAREHOUSE_INPUT_MANAGEMENT_H
#define AUTOMATED_WAREHOUSE_INPUT_MANAGEMENT_H

#include <stdio.h>
#include "../utility/types.h"


int input_validation(int layout[HEIGHT][WIDTH], node target);
void input_target(int layout[HEIGHT][WIDTH], node* target);
void promptCustomShelf(int layout[HEIGHT][WIDTH], node* target);


#endif //AUTOMATED_WAREHOUSE_INPUT_MANAGEMENT_H