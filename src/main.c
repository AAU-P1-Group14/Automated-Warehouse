#include "algorithms/bfs.h"
#include "utility/misc.h"
#include "managers/input_manager.h"
#include "managers/array_manager.h"

int main(void) {
    static int layout[HEIGHT][WIDTH]; // Creating an empty static 2D array to store the warehouse layout
    static int vis[HEIGHT][WIDTH];

    init_array(layout);

    node target = (node){0,0};

    promptCustomShelf(layout,&target);

    printf("%d, %d", target.x, target.y);

    bfs(layout, vis, target, (node){16, 4});

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



