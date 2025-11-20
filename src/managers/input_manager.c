#include "input_manager.h"

#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

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
    srand(time(NULL));

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
            random_target(layout, target_row, target_col);
            break;

        default:
            printf("Invalid input\n");
            break;
        }
    }
}

void random_target(int layout[HEIGHT][WIDTH], int* target_row, int* target_col) {
    // 2D array to store the coordinates of all shelves
    node shelf_arr[HEIGHT * WIDTH];

    // Initialising shelf_counter to count the amount of shelves found in the layout;
    int shelf_counter = 0;

    // Looping through all columns
    for (int row = 0; row < HEIGHT; row++)
    {
        //Looping through all rows
        for (int col = 0; col < WIDTH; col++)
        {
            // If the coordinate is a shelf, assign that coordinate to
            // the shelf_arr and increase shelf_counter by 1;
            if (layout[row][col] == shelf)
            {
                shelf_arr[shelf_counter] = (node){col, row};
                shelf_counter++;
            }
        }
    }

    if (shelf_counter == 0) {
        printf("ERROR: No shelves was found!\n");
        return;
    }

    // Random number to choose a target
    int random_target = rand() % (shelf_counter + 1);

    // Choosing a random shelf (row and column)
    *target_row = shelf_arr[random_target].y;
    *target_col = shelf_arr[random_target].x;

    if (!input_validation(layout, *target_row, *target_col)) printf("Invalid target: (%d, %d)!\n\n", *target_row, *target_col);
    else printf("Target shelf: (%d, %d)\n", *target_row, *target_col);
}