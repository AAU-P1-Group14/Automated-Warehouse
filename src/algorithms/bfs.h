#ifndef AUTOMATED_WAREHOUSE_BFS_H
#define AUTOMATED_WAREHOUSE_BFS_H

#include <stdbool.h>
#include <stdio.h>
#include "../utility/types.h"

bool isValid(int grid[HEIGHT][WIDTH], node current, node target);
int bfs(int grid[HEIGHT][WIDTH],node target,node current,int* tiles);

#endif //AUTOMATED_WAREHOUSE_BFS_H