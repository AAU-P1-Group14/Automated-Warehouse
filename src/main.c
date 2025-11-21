#include "algorithms/bfs.h"
#include "utility/misc.h"
#include "managers/array_manager.h"
#include "managers/input_manager.h"
#include "managers/main_menu.h"

int debug = 0;

int main(void) {
  
    // Initialising arrays
    // Creating an empty static 2D array to store the warehouse layout
    // Static 0-initialises
    static int layout[HEIGHT][WIDTH]; // Creating an empty static 2D array to store the warehouse layout

    int break_loop = 0;

    // Setting default layout to 1
    int layout_selected = 1;

    // Set shelf_selection for random shelf
    int shelf_selection = 0;

    // Creating target point
    node target_t = {0,0};

    init_array(layout);

    random_target(layout, &target_t);

    // Start menu
    clear_terminal();
    while (!break_loop) {
        print_menu(layout_selected, shelf_selection);
        break_loop = select(layout, &layout_selected, &target_t);
    }
    clear_terminal();

    // Creating array that contains coordinates of the robot path
    static node path[HEIGHT * WIDTH];

    for (int i = 0; i < 1; i++) {

        // Input target in layout array
        layout[target_t.y][target_t.x] = target;

        int tiles = 0;

        switch (i) {
            case 0:

                // Path finding algorithm, changing the layout with a path to the target point
                bfs(layout, target_t, (node){16, 4}, &tiles, path);

                // Path finding algorithm, changing the layout with a path to the target point
                bfs(layout, (node){16, 31}, target_t, &tiles, path);

                break;

            case 1:
                break;

            default:
                break;
        }
                  
        // Print the layout
        print_array(layout,false);

        //Prints stats
        printf("Final route was %d tiles\n", tiles);

        //Clears the path from the layout array
        clear_path(layout, path, &tiles, target_t);
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
    getchar();

    return 0;
}