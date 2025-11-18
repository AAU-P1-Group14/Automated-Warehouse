#include "input_manager.h"

#include <stdbool.h>

void input_target(int layout[HEIGHT][WIDTH], int* target_row, int* target_col){
    while (1) {
        printf("Enter target (row col): ");
        scanf("%d %d", target_row, target_col);

        int valid_target = input_validation(layout, *target_row, *target_col);
        if (!valid_target){
            printf("Invalid target: Must be shelf or drop-off.\n\n");
        }
        else break;
    }
}

int input_validation(int layout[HEIGHT][WIDTH], int target_row, int target_col){
    if (target_row > HEIGHT || target_row < 0 || target_col > WIDTH || target_col < 0) {
        return 0;
    }

    if (layout[target_row][target_col] != shelf && layout[target_row][target_col] != drop_off) {
        return 0;
    }

    return 1;
}

void promptCustomShelf(int layout[HEIGHT][WIDTH], int* target_row, int* target_col)
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
            input_target(layout, target_row, target_col);
            break;
        case 'n':
            validInput = 1;
            *target_row = 3;
            *target_col = 3;
            break;

        default:
            printf("Invalid input\n");
            break;
        }
    }
}