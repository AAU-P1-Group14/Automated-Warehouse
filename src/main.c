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
        int target_row = 0;
        int target_col = 0;
        
        // Prompt the user to use a custom or pre-defined shelf
        promptCustomShelf(layout, &target_row, &target_col);

        int tiles_one;
        int tiles_two;

        switch (i) {
            case 0:
   
            // Path finding algorithm, changing the layout with a path to the target point
            bfs(layout, target_row, target_col, 16, 4, &tiles_one);

            // Print the layout
            print_array(layout);

            // Path finding algorithm, changing the layout with a path to the target point
            bfs(layout, 16, 31, target_row, target_col, &tiles_two);
  

            break;

            case 1:
                break;


            default:
                break;
        }
                  
            // Print the layout
            print_array(layout);

            printf("Final route was %d tiles", tiles_one + tiles_two);

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



