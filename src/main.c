#include "algorithms/bfs.h"
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
        node target_t = {0,0};
        
        // Prompt the user to use a custom or pre-defined shelf
        promptCustomShelf(layout,&target_t);

        // Input target in layout array
        layout[target_t.y][target_t.x] = target;

        int tiles_one;
        int tiles_two;

        switch (i) {
            case 0:
                // Path finding algorithm, changing the layout with a path to the target point
                bfs(layout, target_t, (node){16, 4}, &tiles_one);

                // Path finding algorithm, changing the layout with a path to the target point
                bfs(layout, (node){16, 31}, target_t, &tiles_two);

                break;

            case 1:
                break;

            default:
                break;
        }
                  
        // Print the layout
        print_array(layout,false);

        // Reset layout array
        // Clear target
        layout[target_t.y][target_t.x] = shelf;

        // Clear path in layout array and clear path node array
        for (int i = 0; i < tiles_one+tiles_two; ++i)
        {
            printf("i: %d\n", i);
            printf("Layout plads (y,x): %d\n", layout[path[i].y][path[i].x]);
            printf("path[i].y, path[i].x: %d,%d\n", path[i].y, path[i].x);
            layout[path[i].y][path[i].x] = vacant;
            path[i].y = 0;
            path[i].x = 0;
        }

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