#ifndef AUTOMATED_WAREHOUSE_TYPES_H
#define AUTOMATED_WAREHOUSE_TYPES_H

//#define WIDTH 36
//#define HEIGHT 19
#define MAX_BRANCHES 100

typedef struct {
    int y;
    int x;
} node;

// Using enum for the warehouse layout to make the code more readable
enum pos {vacant, v_line, h_line, robot, shelf, drop_off, charging, path_enum, target};

enum direction_enum {up, left, right, down};

static int vis[1000][1000];



#endif //AUTOMATED_WAREHOUSE_TYPES_H