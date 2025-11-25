#include "main_menu.h"


void print_menu(int layout_selected, int shelf_selection, node target, int bench, bool procedural) {
    if (procedural) printf("> Target shelf: Procedural\n");
    else if (shelf_selection) printf("> Target shelf: Custom (%d, %d)\n", target.y, target.x);
    else printf("> Target shelf: Random\n");

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

int select(int layout[HEIGHT][WIDTH], int* layout_selected, int* shelf_selected, node* target, int* bench, bool* procedural) {
    int chosen;
    printf("\n\nChoose: ");
    scanf(" %d", &chosen);

    switch (chosen)
    {
    case 1:
        if (*layout_selected) {
            clear_terminal();
            return true;
        }

        clear_terminal();
        return false;

    case 2:
        // Prompt the user to use a custom or pre-defined shelf
        clear_terminal();
        print_array(layout,true);
        *procedural = false;
        input_target(layout, target);
        clear_terminal();
        *shelf_selected = 1;
        return false;
    
    case 3:
        clear_terminal();
        prompt_procedural(procedural);
        clear_terminal();
        if (!procedural) *target = random_target(layout);
        *shelf_selected = 0;
        return false;
    
    case 4:
        clear_terminal();
        init_array(layout);
        *layout_selected = 1;
        return false;
    
    case 5:
        /*
        TODO: TILFØJ DYNAMISK LAYOUT EDITOR
        */
        clear_terminal();
        *layout_selected = 0;
        return false;

    case 6:
        clear_terminal();
        select_bench(bench);
        return false;
    
    case 0:
        exit(1);
    
    default:
        clear_terminal();
        while (getchar() != '\n');
        printf("INVALID INPUT\n");
        return false;
    }
}