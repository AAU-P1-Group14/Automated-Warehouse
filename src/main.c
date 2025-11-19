#include "algorithms/bfs.h"
#include "utility/misc.h"
#include "managers/input_manager.h"
#include "managers/array_manager.h"

int debug = 0;

int main(void) {
    // Initialising arrays
    // Creating an empty static 2D array to store the warehouse layout
    // Static 0-initialises
    static int layout[HEIGHT][WIDTH];
    // Creating a 2D array storing weather the coordinate is visited
    static int vis[HEIGHT][WIDTH];

    // Creating the layout in the array
    init_array(layout);

    // Creating target point
    int target_row = 0;
    int target_col = 0;

    // Prompt the user to use a custom or pre-defined shelf
    promptCustomShelf(layout,&target_row,&target_col);

    // Path finding algorithm, changing the layout with a path to the target point
    bfs(layout, vis, target_row, target_col, 16, 4);

    // Print the layout
    print_array(layout);

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



