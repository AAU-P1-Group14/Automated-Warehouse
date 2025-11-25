#ifndef AUTOMATED_WAREHOUSE_BFS_H
#define AUTOMATED_WAREHOUSE_BFS_H

#include <stdbool.h>
#include <stdio.h>
#include "../utility/types.h"
#include "../utility/misc.h"

bool isValid(int grid[HEIGHT][WIDTH], node current, node target);
int bfs(int grid[HEIGHT][WIDTH],node target_t,node current,int* tiles,long long* total_tiles,node path[HEIGHT * WIDTH],bool firstcase);

#endif //AUTOMATED_WAREHOUSE_BFS_H