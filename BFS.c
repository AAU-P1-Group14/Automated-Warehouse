#include <stdio.h>
#include <stdbool.h>

#define WIDTH 36
#define HEIGHT 19
#define MAX_BRANCHES 100

// Using enum for the warehouse layout to make the code more readable
enum pos {vacant, v_line, h_line, robot, shelf, drop_off, charging, path_enum};

typedef struct {
    int x;
    int y;
} node;


bool isValid(int vis[HEIGHT][WIDTH], int grid[HEIGHT][WIDTH], int row, int col, int target_row, int target_col)
{
    // If cell lies out of bounds
    if (row < 0 || col < 0 || row >= HEIGHT || col >= WIDTH)
        return false;

    // If cell is already visited
    if (vis[row][col])
        return false;

    if (row == target_row && col == target_col) return true;

    switch  (grid[row][col]) {
        case v_line: case h_line: case shelf:
            return false;
    }

    // Otherwise
    return true;
}


// Function to perform the BFS traversal
int BFS(
    int grid[HEIGHT][WIDTH], int vis[HEIGHT][WIDTH],
    int target_row, int target_col,
    int row, int col)
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
    queue[back] = (node){row,col};
    back++;
    vis[row][col] = 1;

    // (valgfrit) markér start i grid, hvis du vil
    // grid[row][col] = visited;

    // BFS
    int found = 0;
    while (front < back) {

        int x = queue[front].x;
        int y = queue[front].y;
        front++;

        // Hvis vi har ramt målet, kan vi stoppe
        if (x == target_row && y == target_col) {
            found = 1;
            break;
        }

        // Go to the adjacent cells
        for (int i = 0; i < 4; i++) {

            node adj = {x + dRow[i], y + dCol[i]};

            if (isValid(vis, grid, adj.x, adj.y, target_row, target_col)) {
                queue[back] = adj;
                back++;

                vis[adj.x][adj.y] = 1;
                //grid[adjx][adjy] = visited;

                parent[adj.x][adj.y] = (node){x,y};
            }
        }
    }

    if (!found) {
        printf("Ingen vej fundet til (%d, %d)\n", target_row, target_col);
        return 0;
    }

    // Backtrack ruten fra target til start
    node path[HEIGHT * WIDTH];
    int path_len = 0;

    node child = (node){target_row, target_col};

    while (!(child.x == row && child.y == col)) {
        path[path_len] = child;
        path_len++;

        // Safety check hvis noget går galt
        if (parent[child.x][child.y].x == -1 && parent[child.x][child.y].y == -1) {
            printf("Fejl under backtracking\n");
            return 0;
        }

        child = parent[child.x][child.y];
    }

    // Til sidst også startcellen
    path[path_len] = (node){row,col};
    path_len++;

    // Print ruten fra start → target
    for (int i = path_len - 1; i >= 0; i--) {
        // printf("(%d, %d) ", path_row[i], path_col[i]);
        if (!(path[i].x == row && path[i].y == col) && !(path[i].x == target_row && path[i].y == target_col)) {
            grid[path[i].x][path[i].y] = path_enum;
        }
    }
    printf("\n");

    return 1;
}

