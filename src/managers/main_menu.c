#include "main_menu.h"
#include "array_manager.h"
#include "../utility/misc.h"
#include <stdlib.h>

#include "input_manager.h"


void print_menu(int layout_selected, int shelf_selection, node target) {
    if (shelf_selection) printf("> Shelf: Custom (%d, %d)\n", target.y, target.x);
    else printf("> Shelf: Random\n");

    if (layout_selected) printf("> Layout: Predefined\n");
    else printf("> Layout: Dynamic\n");

    printf("\n--------------------------------\n");
    printf("(1) Start simulation\n");
    printf("(2) Custom shelf\n");
    printf("(3) Predefined layout\n");
    printf("(4) Dynamic layout\n");
    printf("\n(0) Exit\n");
    printf("--------------------------------\n");
}

int select(int layout[HEIGHT][WIDTH], int* layout_selected, int* shelf_selected, node* target) {
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
        clear_terminal();
        *shelf_selected = 1;
        return 0;
    
    case 3:
        clear_terminal();
        init_array(layout);
        *layout_selected = 1;
        return 0;
    
    case 4:
        /*
        TODO: TILFØJ DYNAMISK LAYOUT EDITOR
        */
        clear_terminal();
        *layout_selected = 0;
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