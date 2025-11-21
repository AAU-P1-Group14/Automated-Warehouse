#include "main_menu.h"
#include "array_manager.h"
#include "../utility/misc.h"
#include <stdlib.h>

#include "input_manager.h"


void print_menu(int layout_selected, int shelf_selection) {
    if (layout_selected == 1) printf("Default layout selected\n");
    else if (layout_selected) printf("Layout selected\n");
    else printf("No layout selected\n");

    if (shelf_selection == 0) printf("Random shelf selected\n");
    else if (shelf_selection == 1) printf("Custom shelf selected\n");
    else printf("No layout selected\n");

    printf("\n--------------------------------\n");
    printf("(1) Start simulation\n");
    printf("(2) Custom shelf\n");
    printf("(3) Predefined layout\n");
    printf("(4) Dynamic layout\n");
    printf("\n(0) Exit\n");
    printf("--------------------------------\n");
}

int select(int layout[HEIGHT][WIDTH], int* layout_selected, node* target) {
    int chosen;
    printf("\n\nChoose: ");
    scanf(" %d", &chosen);

    switch (chosen)
    {
    case 1:
        if (*layout_selected) {
            clear_terminal();
            return 1;
        }

        clear_terminal();
        return 0;

    case 2:
        // Prompt the user to use a custom or pre-defined shelf
        clear_terminal();
        print_array(layout,true);
        input_target(layout, target);
        break;
    
    case 3:
        clear_terminal();
        init_array(layout);
        *layout_selected = 1;
        return 0;
    
    case 4:
    // Lav dynamisk setup
        clear_terminal();
        return 0;
    
    case 0:
        exit(1);
    
    default:
        clear_terminal();
        while (getchar() != '\n');
        printf("INVALID INPUT\n");
        return 0;
    }
}