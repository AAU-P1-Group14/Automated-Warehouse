#ifndef AUTOMATED_WAREHOUSE_BFS_H
#define AUTOMATED_WAREHOUSE_BFS_H

#define WIDTH 36
#define HEIGHT 19
#define MAX_BRANCHES 100

bool isValid(int vis[HEIGHT][WIDTH], int grid[HEIGHT][WIDTH], int row, int col, int target_row, int target_col);
int BFS(int grid[HEIGHT][WIDTH], int vis[HEIGHT][WIDTH], int target_row, int target_col, int row, int col);

// Using enum for the warehouse layout to make the code more readable
enum pos {vacant, v_line, h_line, robot, shelf, drop_off, charging, path_enum};


#endif //AUTOMATED_WAREHOUSE_BFS_H