#include <stdint.h>

#include "algorithms/bfs.h"
#include "algorithms/dfs.h"
#include "algorithms/worst_case.h"
#include "utility/misc.h"
#include "managers/array_manager.h"
#include "managers/input_manager.h"
#include "managers/main_menu.h"
#include "managers/algorithm_manager.h"
#include "dynamic_layout/dynamic_warehouse.h"
#include <time.h>
#include <stdlib.h>
#include <sys/timeb.h>

int debug = false;

int main(void) {
    // Initialising randomness for random target selection
    const int height = 19;
    const int width  = 36;
    //int* height = &h;
    //int* width = &w;


    srand(time(NULL));
  
    // Initialising arrays
    // Creating an empty static 2D array to store the warehouse layout
    // Static 0-initialises
    static int layout[height][width]; // Creating an empty static 2D array to store the warehouse layout

    // Creating target point
    node target_t = {0,0};

    init_array(height, width, layout);

    target_t = random_target(&height, &width, layout);

    // Boolean var to define when to break the main menu
    int break_main_menu = false;
    // Setting layout (1: pre determined, 0: dynamic) 
    int layout_selected = 1;
    // Set shelf_selection (0: Random, 1: Custom)
    int shelf_selection = 0;
    //Number of benches
    int bench = 1;
    //Should the targets be procedurally generated
    bool procedural = 1;
    printf("1");
    // Start menu
    //clear_terminal();
    while (!break_main_menu) {
        print_menu(layout_selected, shelf_selection, target_t, bench, procedural);
        break_main_menu = select(&height, &width, layout, &layout_selected, &shelf_selection, &target_t, &bench, &procedural);
    }
    printf("1.5");
    clear_terminal();
    printf("2");
    if (layout_selected == 1) {
        printf("3");
        run_algorithms(height, width, layout, target_t, bench, procedural, debug);

    } else {
        printf("4");
        int layout2[mDimensions[0]][mDimensions[1]];
        const int height2 = mDimensions[0];
        const int width2  = mDimensions[1];
        run_algorithms(height2, width2, layout2, target_t, bench, procedural, debug);

    }

  
    // When running in external console, the program only closes after enter is pressed
    getchar();
    getchar();

    return 0;
}