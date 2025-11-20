#include "input_manager.h"

#include <stdbool.h>

void input_target(int layout[HEIGHT][WIDTH], node* target){
    while (1) {
        printf("Enter target (row col): ");
        scanf("%d %d", &target->y, &target->x);

        int valid_target = input_validation(layout, *target);
        if (!valid_target){
            printf("Invalid target: Must be shelf or drop-off.\n\n");
        }
        else break;
    }
}

int input_validation(int layout[HEIGHT][WIDTH], node target){
    if (target.y > HEIGHT || target.y < 0 || target.x > WIDTH || target.x < 0) {
        return 0;
    }

    if (layout[target.x][target.y] != shelf && layout[target.x][target.y] != drop_off) {
        return 0;
    }

    return 1;
}

void promptCustomShelf(int layout[HEIGHT][WIDTH], node* target)
{
    char input;
    bool validInput = 0;

    while (validInput == 0)
    {
        printf("Choose a custom shelf? y/n\n");
        scanf(" %c", &input);

        switch (input)
        {
        case 'y':
            validInput = 1;
            input_target(layout, target);
            break;
        case 'n':
            validInput = 1;
            *target = (node){3,3};
            break;

        default:
            printf("Invalid input\n");
            break;
        }
    }
}