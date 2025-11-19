#ifndef AUTOMATED_WAREHOUSE_BFS_H
#define AUTOMATED_WAREHOUSE_BFS_H

#include <stdbool.h>
#include <stdio.h>
#include "../utility/types.h"

bool is_valid(int vis[HEIGHT][WIDTH], int grid[HEIGHT][WIDTH], int row, int col, int target_row, int target_col);
int bfs(int grid[HEIGHT][WIDTH], int target_row, int target_col, int row, int col, int* tiles);

#endif //AUTOMATED_WAREHOUSE_BFS_H