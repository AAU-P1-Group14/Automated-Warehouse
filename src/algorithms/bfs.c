#include "bfs.h"

//#define WIDTH 36
//#define HEIGHT 19
#define MAX_BRANCHES 100


bool bfs_is_valid(int height, int width, int grid[height][width], node current, node target)
{
    // If cell lies out of bounds
    if (current.x < 0 || current.y < 0 || current.y >= height || current.x >= width)
        return false;

    // If cell is already visited
    if (vis[current.y][current.x])
        return false;
        
    // If the shelf is the target, return true
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

// Function to perform the BFS traversal
int bfs(
    int height,
    int width,
    int grid[height][width],
    long* direction_switches,
    node target_t,
    node start,
    long* total_tiles,
    node path[height * width],
    bool lastcase)
{
    // Simple queue implementation using arrays
    node queue[height * width];

    // Front and back end of queue
    int front = 0, back = 0;

    // Used for calculating direction change
    int direction;

    // Direction vectors (op, højre, ned, venstre)
    int dRow[] = { -1, 0, 1, 0 };
    int dCol[] = { 0, 1, 0, -1 };

    // Parent-array for backtracking
    node parent[height][width];

    // Init parents til -1 (ingen forælder)
    for (int r = 0; r < height; r++) {
        for (int c = 0; c < width; c++) {
            parent[r][c] = (node){-1, -1};
        }
    }

    // Mark the starting cell as visited
    // and push it into the queue
    queue[back] = start;
    back++;
    vis[start.y][start.x] = 1;

    // BFS
    int found = false;
    while (front < back) {
        node yx = queue[front];
        front++;

        // If target was hit, stop the loop
        found = cmp_node(yx, target_t);
        if (found) break;

        // Go to the adjacent cells
        for (int i = 0; i < 4; i++) {

            node adj = {yx.y + dRow[i], yx.x + dCol[i]};

            if (bfs_is_valid(height, width, grid, adj, target_t)) {
                queue[back] = adj;
                back++;

                // Marking valid adjecent points as visited
                vis[adj.y][adj.x] = 1;

                //Makes sure that when searching for adjecent grids their value is the parent grid.
                parent[adj.y][adj.x] = yx;
            }
        }
    }

    if (!found) {
        printf("No path found to target: (%d, %d)\n", target_t.y, target_t.x);
        return false;
    }

    // Backtrack the path from target to start
    int path_len = 0;

    node child = target_t;

    // Running while we haven't back-traced to the starting point
    while (!cmp_node(child, start)) {

        // Assigning current position to path array and handling multible BFS runs
        path[path_len] = child;
        path_len++;

        // Safety check if something goes wrong
        if (parent[child.y][child.x].y == -1 && parent[child.y][child.x].x == -1) {
            printf("Error in backtracking\n");
            return false;
        }

        // Calculating direction changes
        if (parent[child.y][child.x].x < child.x) {
            if (direction != left) {
                (*direction_switches)++;
                direction = left;
            }
        }

        if (parent[child.y][child.x].x > child.x) {
            if (direction != right) {
                (*direction_switches)++;
                direction = right;
            }
        }

        if (parent[child.y][child.x].y < child.y) {
            if (direction != down) {
                (*direction_switches)++;
                direction = down;
            }
        }

        if (parent[child.y][child.x].y > child.y) {
            if (direction != up) {
                (*direction_switches)++;
                direction = up;
            }
        }

        // Progressing by setting parent as the new child
        child = parent[child.y][child.x];
    }

    // Subtracting "starting direction change"
    if (*direction_switches > 0) (*direction_switches)--;

    // At the end, add the start position to the path
    path[path_len] = start;
    path_len++;

    // Add the path in the warehouse layout
    for (int i = path_len - 1; i >= 0; i--) {

        // Update layout array, if it is not the starting og end point
        if (!cmp_node(path[i], start) && !cmp_node(path[i], target_t)) {
            if (lastcase) grid[path[i].y][path[i].x] = path_enum;
        }
    }

    // Incrementing totalt tile length
    *total_tiles += path_len;

    // Clearing visted array
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            vis[i][j] = 0;
        }
    }
    return true;
}

