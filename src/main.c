// TEST
#include "algorithms/bfs.h"
#include "utility/misc.h"
#include "managers/input_manager.h"
#include "managers/array_manager.h"

int main(void) {
    static int layout[HEIGHT][WIDTH]; // Creating an empty static 2D array to store the warehouse layout
    static int vis[HEIGHT][WIDTH];

    init_array(layout);

    int target_row = 0;
    int target_col = 0;

    promptCustomShelf(layout,&target_row,&target_col);

    bfs(layout, vis, target_row, target_col, 16, 4);

    print_array(layout);

/*
    int len_vis = sizeof(vis) / sizeof(vis[0]);
    for (int j = 0; j < HEIGHT; j++) {
        for (int i = 0; i < WIDTH; i++) {
            printf("%d", vis[j][i]);
        }
        printf("\n");
    }
*/
    // When running in external console, the program only closes after enter is pressed
    getchar();
    getchar();

    return 0;
}



