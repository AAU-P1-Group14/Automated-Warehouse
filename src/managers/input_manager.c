#include "input_manager.h"
#include "array_manager.h"
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

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
        printf("OUT OF BOUNDS");
        return 0;
    }

    if (layout[target.y][target.x] != shelf && layout[target.y][target.x] != drop_off) {
        printf("NOT A SHELF");
        return 0;
    }

    return 1;
}

void promptCustomShelf(int layout[HEIGHT][WIDTH], node* target)
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
                print_num_array(layout);
            input_target(layout, target);
            break;
        case 'n':
            random_target(layout, target);
            validInput = input_validation(layout, *target);
            break;

        default:
            printf("Invalid input\n");
            break;
        }
    }
}

void random_target(int layout[HEIGHT][WIDTH], node* target) {
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
                shelf_arr[shelf_counter] = (node){row, col};
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
    *target = shelf_arr[random_target];

    printf("Target shelf: (%d, %d)\n", target->y, target->x);
}