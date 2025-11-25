#ifndef AUTOMATED_WAREHOUSE_DYNAMIC_WAREHOUSE_H
#define AUTOMATED_WAREHOUSE_DYNAMIC_WAREHOUSE_H

#include <stdio.h>
#include <stdlib.h>
#include "../utility/types.h"
#include "../managers/array_manager.h"

extern char* mLayout;
extern int* mDimensions;

int* dynamicWarehouseDesign(int* height, int* width);

#endif //AUTOMATED_WAREHOUSE_DYNAMIC_WAREHOUSE_H