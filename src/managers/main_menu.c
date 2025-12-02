#include "main_menu.h"
#include "../dynamic_layout/dynamic_warehouse.h"


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

int select(int *height, int *width, node* charging, node* dropoff, int layout[*height][*width], int* layout_selected, int* shelf_selected, node* target, int* bench, bool* procedural) {
    int chosen;
    printf("\n\nChoose a number: ");
    scanf(" %d", &chosen);

    clear_terminal();
    switch (chosen)
    {
    case 1:
        if (*layout_selected != 1 && *layout_selected != 0) {
            return false;
        }

        if (*shelf_selected == 0 && !(*procedural)) *target = random_target(*height, *width, layout);
        return true;

    case 2:
        // Prompt the user to use a custom or pre-defined shelf
        print_array(*height, *width, layout,true);
        *procedural = false;
        input_target(*height, *width, layout, target);
        clear_terminal();
        *shelf_selected = 1;
        return false;
    
    case 3:
        prompt_procedural(procedural);
        clear_terminal();
        *shelf_selected = 0;
        return false;
    
    case 4:
        *charging = (node){16, 4};
        *dropoff = (node){16, 31};
        *height = 19;
        *width  = 36;
        init_array(19, 36, layout);
        *target = random_target(*height, *width, layout);
        *layout_selected = 1;
        *shelf_selected = 0;
        return false;
    
    case 5:{
        int yShelfSections;
        int yShelfDivider;
        int xShelfWidth;
        int sectionWidth;

        setHegihtWidth(height, width, &yShelfSections, &yShelfDivider, &xShelfWidth, &sectionWidth);
        dynamicWarehouseDesign(*height, *width, layout, charging, dropoff, yShelfSections, yShelfDivider, xShelfWidth, sectionWidth);
        print_array(*height, *width, layout, false);
        *target = random_target(*height, *width, layout);
        *layout_selected = 0;
        *shelf_selected = 0;
        return false;
    }

    case 6:
        select_bench(bench);
        return false;
    
    case 0:
        exit(1);
    
    default:
        while (getchar() != '\n');
        printf("INVALID INPUT\n");
        return false;
    }
}