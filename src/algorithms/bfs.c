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
    node target_t,
    node current,
    int* tiles,
    long long* total_tiles,
    node path[height * width],
    bool firstcase)
{
    // Simple queue implementation using arrays
    node queue[height * width];
    int front = 0, back = 0;

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
    queue[back] = current;
    back++;
    vis[current.y][current.x] = 1;

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

                vis[adj.y][adj.x] = 1;
                //grid[adjy][adjx] = visited;

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

    while (!cmp_node(child, current)) {
        path[*tiles+path_len] = child;
        path_len++;

        // Safety check if something goes wrong
        if (parent[child.y][child.x].y == -1 && parent[child.y][child.x].x == -1) {
            printf("Error in backtracking\n");
            return false;
        }
        child = parent[child.y][child.x];
    }

    // At the end, also the start position
    path[*tiles + path_len] = current;
    path_len++;

    // Add the path in the warehouse layout
    for (int i = path_len - 1; i >= 0; i--) {
        // printf("(%d, %d) ", path_row[i], path_col[i]);
        if (!cmp_node(path[*tiles+i], current) && !cmp_node(path[*tiles+i], target_t)) {
            if (firstcase) grid[path[*tiles+i].y][path[*tiles+i].x] = path_enum;
        }
    }

    *total_tiles += path_len;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            vis[i][j] = 0;
        }
    }
    return true;
}

