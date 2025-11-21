#include "algorithms/bfs.h"
#include "algorithms/dfs.h"
#include "utility/misc.h"
#include "managers/array_manager.h"
#include "managers/input_manager.h"

int debug = 0;

int main(void) {
  
    // Initialising arrays
    // Creating an empty static 2D array to store the warehouse layout
    // Static 0-initialises
    static int layout[HEIGHT][WIDTH]; // Creating an empty static 2D array to store the warehouse layout

    for (int i = 0; i < 2; i++) {
        
        // Creating the layout in the array
        init_array(layout);
   
        // Creating target point
        node target = {0,0};
        
        // Prompt the user to use a custom or pre-defined shelf
        promptCustomShelf(layout,&target);



        int tiles_one;
        int tiles_two;

        switch (i) {
            case 0:
                // Path finding algorithm, changing the layout with a path to the target point
                bfs(layout, target, (node){16, 4}, &tiles_one);

                // Print the layout
                print_array(layout);

                // Path finding algorithm, changing the layout with a path to the target point
                bfs(layout, (node){16, 31}, target, &tiles_two);

                break;

            case 1:
                // Path finding algorithm, changing the layout with a path to the target point
                dfs(layout, target, (node){16, 4}, &tiles_one);

                // Print the layout
                print_array(layout);

                // Path finding algorithm, changing the layout with a path to the target point
                dfs(layout, (node){16, 31}, target, &tiles_two);

                break;

            default:
                break;
        }
                  
        // Print the layout
        print_array(layout);

        printf("Final route was %d tiles\n", tiles_one + tiles_two);
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