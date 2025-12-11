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

int main(void) {
    int debug = false;

    // Setting an output buffer, for faster print of layouts
    setvbuf(stdout, NULL, _IOFBF, 4096);

    // Creating a seed for the rand function
    srand(time(NULL));
  
    // Initialising arrays
    // Creating an 2D array to store the warehouse layout
    int layout[200][200];

    // Creating default position for drop-off and the charging point for the predefined layout
    node charging = (node){16, 4};
    node dropoff = (node){16, 31};

    // Initialising default height and width for predefined layout
    int height = 19;
    int width  = 36;

    // Initialising the default predefined layout
    init_array(height, width, layout);

    // Creating a node for the target
    node target_t;

    // Setting default layout (1: pre determined, 0: dynamic)
    int layout_selected = 1;

    // Set default shelf_selection (0: Random, 1: Custom)
    int shelf_selection = 0;

    // Default number of benches
    int bench = 1;

    // Defaults the targets to be procedurally generated
    bool procedural = true;

    // Start menu
    do {
        // Variable to define when to break the main menu
        int break_main_menu = 0;

        // Clearing the terminal
        clear_terminal();

        // Running the main menu, until the user choose to run the simulation
        while (!break_main_menu) {

            // Printing the menu
            print_menu(layout_selected, shelf_selection, target_t, bench, procedural);

            // Navigating the menu
            break_main_menu = select(&height, &width, &charging, &dropoff, layout, &layout_selected,
                &shelf_selection, &target_t, &bench, &procedural);
        }

        // Running all the algorithms
        run_algorithms(height, width, layout, charging, dropoff, target_t, bench, procedural, debug);


        printf("Press enter to return to main menu..\n");

        fflush(stdout);

        // When running in external console, the program only closes after enter is pressed
        getchar();
        getchar();

    } while(true);

    return 0;
}