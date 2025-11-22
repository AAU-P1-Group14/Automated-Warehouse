#include "algorithms/bfs.h"
#include "algorithms/dfs.h"
#include "utility/misc.h"
#include "managers/array_manager.h"
#include "managers/input_manager.h"
#include "managers/main_menu.h"
#include <time.h>
#include <stdlib.h>

int debug = 0;

int main(void) {
    // Initialising randomness for random target selection
    srand(time(NULL));
  
    // Initialising arrays
    // Creating an empty static 2D array to store the warehouse layout
    // Static 0-initialises
    static int layout[HEIGHT][WIDTH]; // Creating an empty static 2D array to store the warehouse layout

    int break_loop = 0;

    // Setting layout (1: pre determined, 0: dynamic) 
    int layout_selected = 1;

    // Set shelf_selection (0: Random, 1: Custom)
    int shelf_selection = 0;

    // Creating target point
    node target_t = {0,0};

    init_array(layout);

    random_target(layout, &target_t);

    // Start menu
    clear_terminal();
    while (!break_loop) {
        print_menu(layout_selected, shelf_selection, target_t);
        break_loop = select(layout, &layout_selected, &shelf_selection, &target_t);
    }
    clear_terminal();

    // Creating array that contains coordinates of the robot path
    static node path[HEIGHT * WIDTH];

    printf("TARGET SHELF: (%d, %d)\n\n", target_t.y, target_t.x);
    for (int i = 0; i < 2; i++) {

        // Input target in layout array
        layout[target_t.y][target_t.x] = target;

        int tiles_bfs = 0;
        int tiles_dfs = 0;

        switch (i) {
            case 0:
                // BFS Path finding algorithm, adding the path from charging station to target
                int valid_bfs_1 = bfs(layout, target_t, (node){16, 4}, &tiles_bfs, path);
                if (!valid_bfs_1) {
                    printf("\nUnknown error in BFS to target\n");
                    continue;
                }
                // BFS Path finding algorithm, adding the path from target station to drop-off
                int valid_bfs_2 = bfs(layout, (node){16, 31}, target_t, &tiles_bfs, path);
                if (!valid_bfs_2) {
                    printf("\nUnknown error in BFS to drop-off\n");
                    continue;
                }
                // Print out the result from BFS
                printf("BFS algorithm:\n");
                print_array(layout, false);
                printf("\nFinal route for BFS was %d tiles\n\n\n", tiles_bfs);

                //Clears the path from the layout array
                clear_path(layout, path, &tiles_bfs, target_t);

                break;

            case 1:
                // DFS Path finding algorithm, adding the path from charging station to target
                int valid_dfs_1 = dfs(layout, target_t, (node){16, 4}, &tiles_dfs);
                
                if (!valid_dfs_1) {
                    printf("\nUnknown error in DFS to target\n");
                    continue;
                }
                // DFS Path finding algorithm, adding the path from target station to drop-off
                int valid_dfs_2 = dfs(layout, (node){16, 31}, target_t, &tiles_dfs);
                if (!valid_dfs_2) {
                    printf("\nUnknown error in DFS to drop-off\n");
                    continue;
                }

                // Print out the result from BFS
                printf("DFS algorithm:\n");
                print_array(layout, false);
                printf("\nFinal route for DFS was %d tiles\n", tiles_dfs);
                
                //Clears the path from the layout array
                clear_path(layout, path, &tiles_dfs, target_t);

                break;

            default:
                break;
        }
    }
    
    // Output for debug
    if (debug)
    {
        for (int j = 0; j < HEIGHT; j++)
        {
            for (int i = 0; i < WIDTH; i++)
            {
                printf("%d", vis[j][i]);
            }
            printf("\n");
        }
    }
  
    // When running in external console, the program only closes after enter is pressed
    getchar();

    return 0;
}