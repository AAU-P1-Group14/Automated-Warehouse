#ifndef AUTOMATED_WAREHOUSE_MAIN_MENU_H
#define AUTOMATED_WAREHOUSE_MAIN_MENU_H

#include <stdio.h>
#include <stdlib.h>
#include "../utility/types.h"
#include "../utility/misc.h"
#include "array_manager.h"
#include "input_manager.h"

void print_menu(int layout_selected, int shelf_selection, node target, int bench);
int select(int layout[HEIGHT][WIDTH], int* layout_selected, int* shelf_selected, node* target, int* bench);


#endif //AUTOMATED_WAREHOUSE_MAIN_MENU_H