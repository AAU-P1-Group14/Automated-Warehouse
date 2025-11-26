#include "dfs.h"

#define WIDTH 36
#define HEIGHT 19
#define MAX_BRANCHES 100

bool dfs_is_valid(int grid[HEIGHT][WIDTH], node current, node target)
{

   // If cell lies out of bounds
   if (current.x < 0 || current.y < 0 || current.y >= HEIGHT || current.x >= WIDTH)
        return false;

    if (cmp_node(current, target)) return true;

    // If cell is already visited
    if (vis[current.y][current.x])
        return false;



    // Check if target is reached
    if (cmp_node(current, target))
        return true;

    //Cant walk through shelves or walls
    switch (grid[current.y][current.x]) {
        case v_line: case h_line: case shelf:
            return false;
    }

   // Otherwise
   return true;
}


// Function to perform the DFS traversal
int dfs(
   int grid[HEIGHT][WIDTH], // The warehouse layout
   node target, // Target shelf
   node current, // Current position (start position)
   int* tiles, // Amount of files traveled
   long long* total_tiles,
   bool firstcase) // Should we count tiles
{
    int target_orig = grid[target.y][target.x];

   // We make an array for stack instead of queue.
   // stack is an array that will hold all nodes we might visit.
   node stack[HEIGHT * WIDTH];
   // top = index of the top cell in the stack. ie the first one to check.
   // it makes it start out empty, top is the current "top" of the stock
   int top = -1;

    // Direction vectors (up, right, down, left)
    int dRow[] = { -1, 0, 1, 0 };
    int dCol[] = {  0, 1, 0, -1 };

   // Parent-arrays for backtracking
   node parent[HEIGHT][WIDTH];

   // Init parents to -1 (no parents)
   for (int r = 0; r < HEIGHT; r++) {
       for (int c = 0; c < WIDTH; c++) {
           parent[r][c] = (node){-1, -1};
       }
   }
   //Tracks where we came from to reach each cell.
   //Needed to reconstruct the path after DFS finds the target.

   //++top → move top from -1 → 0, stack[0] = current → push start cell
   stack[++top] = current;
   vis[current.y][current.x] = 1;
   // Mark current as visited (vis[y][x] = 1)
   // DFS begins from here

   // DFS
   int found = false;
   //Check if the stack is empty (top >= 0). If it is empty → DFS is done.
   //Loop continues while stack is not empty.
   while (top >= 0) {
        // yx = current cell being explored (pop from top).
       node yx = stack[top--];
       //Mark visited → prevent loops.

       // DFS explores the most recently added cell first → depth-first.

       // Hvis vi har ramt målet, kan vi stoppe
       found = cmp_node(yx, target);
       if (found) break;

       // Go to the adjacent cells
       for (int i = 0; i < 4; i++) {

           node adj = {yx.y + dRow[i], yx.x + dCol[i]};
           //loops through all possible directions

           if (dfs_is_valid(grid, adj, target)) {
               stack[++top] = adj;
               vis[adj.y][adj.x] = 1;
               // if a cell is valid we push it onto the stack


               parent[adj.y][adj.x] = yx;
               //Set parent → needed to trace path back after DFS.
           }
       }
   }

   if (!found) {
       printf("No path found to target: (%d, %d)\n", target.y, target.x);
       return false;
   }

   // Backtrack the path from target to start position
   node path[HEIGHT * WIDTH];
   int path_len = 0;

   node child = target;

   while (!cmp_node(child, current)) {
       path[path_len] = child;
       path_len++;

       // Safety check if something goes wrong
       if (parent[child.y][child.x].y == -1 && parent[child.y][child.x].x == -1) {
           printf("Error in backtracking\n");
           return false;
       }

       child = parent[child.y][child.x];
   }

   // At the end, also the start position
   path[path_len] = current;
   path_len++;

   // Add the path in the warehouse layout
   for (int i = path_len - 1; i >= 0; i--) {
       // printf("(%d, %d) ", path_row[i], path_col[i]);
       if (!cmp_node(path[i], current) && !cmp_node(path[i], target)) {
           if (grid[path[i].y][path[i].x] == vacant) {
               if (firstcase) grid[path[i].y][path[i].x] = path_enum;
           }
       }
   }

    if (firstcase) *tiles += path_len;
    else *total_tiles += path_len;

   for (int i = 0; i < HEIGHT; i++) {
       for (int j = 0; j < WIDTH; j++) {
           vis[i][j] = 0;
       }
   }
    return true;
}






