#include "bfs.h"
#include "../utility/misc.h"

#define WIDTH 36
#define HEIGHT 19
#define MAX_BRANCHES 100


bool isValid(int grid[HEIGHT][WIDTH], node current, node target)
{
    // If cell lies out of bounds
    if (current.x < 0 || current.y < 0 || current.y >= HEIGHT || current.x >= WIDTH)
        return false;

    // If cell is already visited
    if (vis[current.y][current.x])
        return false;

    if (cmp_node(current, target)) return true;

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
    int grid[HEIGHT][WIDTH],
    node target_t,
    node current,
    int* tiles)
{

    // Simple queue implementation using arrays
    node queue[HEIGHT * WIDTH];
    int front = 0, back = 0;

    // Direction vectors (op, højre, ned, venstre)
    int dRow[] = { -1, 0, 1, 0 };
    int dCol[] = { 0, 1, 0, -1 };

    // Forældre-arrays til backtracking
    node parent[HEIGHT][WIDTH];

    // Init parents til -1 (ingen forælder)
    for (int r = 0; r < HEIGHT; r++) {
        for (int c = 0; c < WIDTH; c++) {
            parent[r][c] = (node){-1, -1};
        }
    }

    // Mark the starting cell as visited
    // and push it into the queue
    queue[back] = current;
    back++;
    vis[current.y][current.x] = 1;

    // (valgfrit) markér start i grid, hvis du vil
    // grid[row][col] = visited;

    // BFS
    int found = 0;
    while (front < back) {

        node yx = queue[front];
        front++;

        // Hvis vi har ramt målet, kan vi stoppe
        if (cmp_node(yx, target_t)) {
            found = 1;
            break;
        }

        // Go to the adjacent cells
        for (int i = 0; i < 4; i++) {

            node adj = {yx.y + dRow[i], yx.x + dCol[i]};

            if (isValid(grid, adj, target_t)) {
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
        printf("Ingen vej fundet til (%d, %d)\n", target_t.y, target_t.x);
        return 0;
    }

    // Backtrack ruten fra target til start

    int path_len = 0;

    node child = target_t;

    while (!cmp_node(child, current)) {
        path[path_len] = child;
        path_len++;

        // Safety check hvis noget går galt
        if (parent[child.y][child.x].y == -1 && parent[child.y][child.x].x == -1) {
            printf("Fejl under backtracking\n");
            return 0;
        }


        child = parent[child.y][child.x];
    }

    // Til sidst også startcellen
    path[path_len] = current;
    path_len++;

    // Print ruten fra start → target
    for (int i = path_len - 1; i >= 0; i--) {
        // printf("(%d, %d) ", path_row[i], path_col[i]);
        if (!cmp_node(path[i], current) && !cmp_node(path[i], target_t)) {
            grid[path[i].y][path[i].x] = path_enum;
        }
    }
    printf("\n");

    *tiles = path_len;

    for (int i = 0; i < HEIGHT; i++) {

        for (int j = 0; j < WIDTH; j++) {
            vis[i][j] = 0;
        }
    }



    return 1;
}

