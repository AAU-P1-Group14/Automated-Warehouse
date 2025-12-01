
#ifndef AUTOMATED_WAREHOUSE_DFS_H
#define AUTOMATED_WAREHOUSE_DFS_H


#include <stdbool.h>
#include <stdio.h>
#include "../utility/types.h"
#include "../utility/misc.h"


// Check if a node is valid to visit
bool dfs_is_valid(int height, int width, int grid[height][width], node current, node target);
int dfs(int height, int width, int grid[height][width], node path[height * width],node target,node current,int* tiles,long long* total_tiles,bool firstcase);






#endif //AUTOMATED_WAREHOUSE_DFS_H




