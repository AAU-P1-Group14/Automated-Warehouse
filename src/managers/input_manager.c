#include "input_manager.h"

void input_target(int layout[HEIGHT][WIDTH], node* target){
    while (1) {
        printf("Enter target (row col): ");

        //We check how many inputs was successfully read from the input buffer.
        int buffer = scanf(" %d %d", &target->y, &target->x);

        //Magic that clears the scanf buffer, so that the inout doesn't stay.
        //It does this by reading the charecters from stdin buffer until the new line.
        while (getchar() != '\n');

        if (buffer != 2) {
            printf("INVALID INPUT.\n");
            continue;
        }

        int valid_target = input_validation(layout, *target);

        if (valid_target){
            break;
        }
    }
}

int input_validation(int layout[HEIGHT][WIDTH], node target){
    if (target.y > HEIGHT || target.y < 0 || target.x > WIDTH || target.x < 0) {
        printf("OUT OF BOUNDS\n");
        return false;
    }

    if (layout[target.y][target.x] != shelf && layout[target.y][target.x] != drop_off) {
        printf("NOT A SHELF\n");
        return false;
    }
    
    return false;
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
}