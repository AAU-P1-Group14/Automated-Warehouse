#ifndef AUTOMATED_WAREHOUSE_BFS_H
#define AUTOMATED_WAREHOUSE_BFS_H

#include <stdbool.h>
#include <stdio.h>
#include "../utility/types.h"
#include "../utility/misc.h"

bool bfs_is_valid(int height, int width, int grid[height][width], node current, node target);
int bfs(int height, int width, int grid[height][width], long* direction_switches,node target_t,node start,int* tiles,long* total_tiles,node path[height * width],bool lastcase);

#endif //AUTOMATED_WAREHOUSE_BFS_H