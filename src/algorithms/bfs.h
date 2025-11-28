#ifndef AUTOMATED_WAREHOUSE_BFS_H
#define AUTOMATED_WAREHOUSE_BFS_H

#include <stdbool.h>
#include <stdio.h>
#include "../utility/types.h"
#include "../utility/misc.h"

bool bfs_is_valid(int height, int width, int grid[height][width], node current, node target);
int bfs(int height, int width, int grid[height][width],node target_t,node current,int* tiles,long long* total_tiles,node path[height * width],bool firstcase);

#endif //AUTOMATED_WAREHOUSE_BFS_H