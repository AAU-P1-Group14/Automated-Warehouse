#ifndef AUTOMATED_WAREHOUSE_BFS_H
#define AUTOMATED_WAREHOUSE_BFS_H

#include <stdbool.h>
#include <stdio.h>
#include "../utility/types.h"

bool is_valid(int vis[HEIGHT][WIDTH], int grid[HEIGHT][WIDTH], node current, node target);
int bfs(int grid[HEIGHT][WIDTH], int vis[HEIGHT][WIDTH],node target,node current);

#endif //AUTOMATED_WAREHOUSE_BFS_H