
#ifndef AUTOMATED_WAREHOUSE_DFS_H
#define AUTOMATED_WAREHOUSE_DFS_H


#include <stdbool.h>
#include <stdio.h>
#include "../utility/types.h"
#include "../utility/misc.h"


// Check if a node is valid to visit
bool isdfsValid(int grid[HEIGHT][WIDTH], node current, node target);
int dfs(int grid[HEIGHT][WIDTH],node target,node current,int* tiles,bool addtiles);






#endif //AUTOMATED_WAREHOUSE_DFS_H




