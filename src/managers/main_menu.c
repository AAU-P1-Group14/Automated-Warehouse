#include "main_menu.h"
#include "../dynamic_layout/dynamic_warehouse.h"


void print_menu(int layout_selected, int shelf_selection, node target, int bench, bool procedural) {

    // Printing whether the target is procedural, random or custom
    if (procedural) printf("> Target shelf: Procedural\n");
    else if (shelf_selection) printf("> Target shelf: Custom (%d, %d)\n", target.y, target.x);
    else printf("> Target shelf: Random\n");

    // Printing whether the layout is predefined or custom
    if (layout_selected) printf("> Layout: Predefined\n");
    else printf("> Layout: Dynamic\n");

    printf("> Benches: %d\n", bench);

    printf("\n--------------------------------\n");
    printf("(1) Start simulation\n\n");

    printf("(2) Custom target\n");
    printf("(3) Random target\n\n");

    printf("(4) Predefined layout\n");
    printf("(5) Dynamic layout\n\n");

    printf("(6) Select benches\n\n");

    printf("(0) Exit\n");
    printf("--------------------------------\n");
}

int select(int *height, int *width, node* charging, node* dropoff, int layout[*height][*width],
    int* layout_selected, int* shelf_selected, node* target, int* bench, bool* procedural) {

    // Variable for which menu is chosen
    int chosen;

    // Print for the user
    printf("\n\nChoose a number: ");
    scanf(" %d", &chosen);

    clear_terminal();
    switch (chosen)
    {
        // Run simulation
    case 1:
        // Input validation on layout_selected
        if (*layout_selected != 1 && *layout_selected != 0) {
            return false;
        }

        if (*shelf_selected == 0 && !(*procedural)) {
            *target = random_target(*height, *width, layout);
            return true;
        }

        // Custom target
    case 2:
        // Prompt the user to use a custom or pre-defined shelf
        print_array(*height, *width, layout,true);

        *procedural = false;

        // Reading the target from user input
        input_target(*height, *width, layout, target);

        clear_terminal();

        // Setting shelf_selected as custom shelf
        *shelf_selected = 1;

        // Go back to main menu
        return false;

        // Random target
    case 3:
        prompt_procedural(procedural);
        clear_terminal();

        // Setting shelf_selected as random
        *shelf_selected = 0;

        // Go back to main menu
        return false;

        // Predefined layout
    case 4:
        *charging = (node){16, 4};
        *dropoff = (node){16, 31};
        *height = 19;
        *width  = 36;
        init_array(19, 36, layout);

        // Chosing a new random target, in case the we come from a custom layout
        *target = random_target(*height, *width, layout);

        // Setting layout_selected as pre-defined
        *layout_selected = 1;

        // Setting shelf_selected as random
        *shelf_selected = 0;

        // Go back to main menu
        return false;

        // Custom layout
    case 5:{
            // Variables for custom layout
            int yShelfSections;
            int yShelfDivider;
            int xShelfWidth;
            int sectionWidth;

            clear_terminal();

            // Calculating shelf section sizes and warehouse dimensions
            setHegihtWidth(height, width, &yShelfSections, &yShelfDivider, &xShelfWidth, &sectionWidth);

            // Designs the custom layout and assigns to the layout array
            dynamicWarehouseDesign(*height, *width, layout, charging, dropoff,
            yShelfSections, yShelfDivider, xShelfWidth, sectionWidth);

            print_array(*height, *width, layout, false);

            // Chosing a new random target, in case the we come from a predefined layout
            *target = random_target(*height, *width, layout);

            // Setting layout_selected as pre-defined
            *layout_selected = 0;

            // Setting shelf_selected as random
            *shelf_selected = 0;

            // Go back to main menu
            return false;
    }

        // Change number of benchmarks
    case 6:
        select_bench(bench);

        // Go back to main menu
        return false;

        // Exit program
    case 0:
        // Shut down program
        exit(1);

        // Default must be an invalid input
    default:
        while (getchar() != '\n');
        printf("INVALID INPUT\n");

        // Go back to main menu
        return false;
    }
}