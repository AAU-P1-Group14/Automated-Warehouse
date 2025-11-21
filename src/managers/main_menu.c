#include "main_menu.h"
#include "array_manager.h"
#include "../utility/misc.h"
#include <stdlib.h>


void print_menu(int layout_selected) {
    if (layout_selected) printf("Layout selected\n\n");
    else printf("No layout selected\n\n");

    printf("\n--------------------------------\n");
    printf("(1) Start simulation\n");
    printf("(2) Predefined layout\n");
    printf("(3) Dynamic layout\n");
    printf("\n(0) Exit\n");
    printf("--------------------------------\n");

}

int select(int layout[HEIGHT][WIDTH], int* layout_selected) {
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

        else {
            clear_terminal();
            return 0;
        };
    
    case 2:
        clear_terminal();
        init_array(layout);
        *layout_selected = 1;
        return 0;
    
    case 3:
    // Lav dynamisk setup
        clear_terminal();
        break;
    
    case 0:
        exit(1);
    
    default:
        clear_terminal();
        while (getchar() != '\n');
        printf("INVALID INPUT\n");
        return 0;
    }
}