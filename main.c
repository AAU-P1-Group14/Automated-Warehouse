#include <stdio.h>
#include <stdbool.h>

#include "funcs.h"

#define WIDTH 36
#define HEIGHT 19
#define MAX_BRANCHES 100

// Using enum for the warehouse layout to make the code more readable
enum pos {vacant, v_line, h_line, robot, shelf, drop_off, charging, path_enum};

void initArray(int layout[HEIGHT][WIDTH]); // prototype of initArray
void input_target(int layout[HEIGHT][WIDTH], int *target_row, int *target_col);
int input_validation(int layout[HEIGHT][WIDTH], int target_row, int target_col);
void printArray(int layout[HEIGHT][WIDTH]); // prototype of printArray
bool isValid(int vis[HEIGHT][WIDTH], int grid[HEIGHT][WIDTH], int row, int col, int target_row, int target_col);
int BFS(int grid[HEIGHT][WIDTH], int vis[HEIGHT][WIDTH], int target_row, int target_col, int row, int col);

typedef struct {
    int x;
    int y;
} node;

int main(void) {
    static int layout[HEIGHT][WIDTH]; // Creating an empty static 2D array to store the warehouse layout
    static int vis[HEIGHT][WIDTH];

    initArray(layout);

    int target_row = 3;
    int target_col = 3;

    input_target(layout, &target_row, &target_col);

    bool found = BFS(layout, vis, target_row, target_col, 16, 4);
    printArray(layout);

/*
    int len_vis = sizeof(vis) / sizeof(vis[0]);
    for (int j = 0; j < HEIGHT; j++) {
        for (int i = 0; i < WIDTH; i++) {
            printf("%d", vis[j][i]);
        }
        printf("\n");
    }
*/

    return 0;
}

void initArray(int layout[HEIGHT][WIDTH]) {


    for (int y_row = 0; y_row < HEIGHT; ++y_row) // Looping through all the rows in the layout array
    {
        for (int x_col = 0; x_col < WIDTH; ++x_col) // Looping through all the coloumns in the layout array
        {
            switch (y_row)
            {
            case 3: case 4: case 7: case 8: case 11: case 12: // These rows should contain shelves

                // (x_col + 2) % 6 == 0 selects the columns where a new shelf block
                // should be placed (every 6th column with an offset of 2)
                if ((x_col+2)%6 == 0) 
                {
                    layout[y_row][x_col] = shelf;
                    layout[y_row][x_col-1] = shelf;
                    layout[y_row][x_col-2] = shelf;
                    layout[y_row][x_col-3] = shelf;
                }
                break;

            case 0: case HEIGHT-1: // At the first and last row, place horizontal lines at every coloum
                layout[y_row][x_col] = h_line;
            }
            switch (x_col)
            {
                case 0: case WIDTH-1: // At the first and last coloum, place vertical lines at every row
                layout[y_row][x_col] = v_line;
            }
        }
    }
    layout[16][4] = charging; // Drop off is hardcoded to be at this spot
    layout[16][31] = drop_off; // Charging station is hardcoded to be at this spot
}

void printArray(int layout[HEIGHT][WIDTH]) {

    for (int y_row = 0; y_row < HEIGHT; ++y_row) // Looping through all the rows in the layout array
    {
        for (int x_col = 0; x_col < WIDTH; ++x_col) // Looping through all the coloumns in the layout array
        {
            switch (layout[y_row][x_col])
            {
            case vacant: printf(" "); break; // If the element is vacant, print a blank space " "

            case v_line: printf("|"); break; // If the element is v_line , print a vertical line "|"

            case h_line: printf("-"); break; // If the element is h_line , print a  horizontal line "-"

            case robot: printf("O"); break; // If the element is robot , print a "O"

            case shelf: printf("X"); break; // If the element is shelf , print a "X"

            case drop_off: printf("D"); break; // If the element is drop_off , print a "D"

            case charging: printf("C"); break; // If the element is charging , print a "C"

            case path_enum: printf("*"); break;
            }
        }
        printf("\n"); // Go to the next row with a new-line
    }
}

void input_target(int layout[HEIGHT][WIDTH], int* target_row, int* target_col){
    while (1) {
        printf("Enter target (row col): ");
        scanf("%d %d", target_row, target_col);

        int valid_target = input_validation(layout, *target_row, *target_col);
        if (!valid_target){
            printf("Invalid target: Must be shelf or drop-off.\n\n");
        }
        else break;
    }
}

int input_validation(int layout[HEIGHT][WIDTH], int target_row, int target_col){
    if (target_row > HEIGHT || target_row < 0 || target_col > WIDTH || target_col < 0) {
        return 0;
    }

    if (layout[target_row][target_col] != shelf && layout[target_row][target_col] != drop_off) {
        return 0;
    }

    return 1;
}

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
