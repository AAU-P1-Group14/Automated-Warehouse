#include "algorithms/bfs.h"
#include "utility/misc.h"
#include "managers/array_manager.h"
#include "managers/input_manager.h"

int main(void) {
    static int layout[HEIGHT][WIDTH]; // Creating an empty static 2D array to store the warehouse layout



    for (int i = 0; i < 2; i++) {

        init_array(layout);

        int target_row = 0;
        int target_col = 0;
        input_target(layout, &target_row, &target_col);

        int tiles_one;
        int tiles_two;

        switch (i) {
            case 0:

            bfs(layout, target_row, target_col, 16, 4, &tiles_one);

            print_array(layout);

            bfs(layout, 16, 31, target_row, target_col, &tiles_two);

            print_array(layout);

            printf("Final route was %d tiles", tiles_one + tiles_two);

            break;

            case 1:
                break;


            default:
                break;
        }



}

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



