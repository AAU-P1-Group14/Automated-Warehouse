
#ifndef AUTOMATED_WAREHOUSE_DFS_H
#define AUTOMATED_WAREHOUSE_DFS_H


#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include "../utility/types.h"
#include "../utility/misc.h"


// Check if a node is valid to visit
bool dfs_is_valid(int height, int width, int grid[height][width], node current, node target);
int dfs(int height, int width, int grid[height][width], long long* direction_switches, node path[height * width],
    node target,node start, long long* total_tiles,bool firstcase, long long* elapsed_dfs);






#endif //AUTOMATED_WAREHOUSE_DFS_H




