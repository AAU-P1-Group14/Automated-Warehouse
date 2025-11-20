#include "array_manager.h"
#include <stdbool.h>


int horizontal_num() {
    bool first = true;
    for (int i = 0; i < WIDTH; i++) {
        if (i % 5 == 0) {
            if (first) {
                printf("  %dx        ", i);
                first = false;
            } else {
                if (i > 9)
                    printf(" %d       ", i);
                else
                    printf("%d        ", i);
                }
            }
        }
    printf("\n");
    }


int vertical_num(int y_row) {
        if (y_row<10) {
            printf("%d ",y_row);
        } else {
            printf("%d",y_row);
        }
    }



void init_array(int layout[HEIGHT][WIDTH]) {

    for (int y_row = 0; y_row < HEIGHT; ++y_row) // Looping through all the rows in the layout array
    {
        for (int x_col = 0; x_col < WIDTH; ++x_col) // Looping through all the coloumns in the layout array
        {
            switch (y_row)
            {
            case 3: case 4: case 7: case 8: case 11: case 12: // These rows should contain shelves

                // (x_col + 2) % 6 == 0 selects the columns where a new shelf block
                // should be placed (every 6th column with an offset of 2)
                if ((x_col+2)%6 == 0)
                {
                    layout[y_row][x_col] = shelf;
                    layout[y_row][x_col-1] = shelf;
                    layout[y_row][x_col-2] = shelf;
                    layout[y_row][x_col-3] = shelf;
                }
                break;

            case 0: case HEIGHT-1: // At the first and last row, place horizontal lines at every coloum
                layout[y_row][x_col] = h_line;
            }
            switch (x_col)
            {
                case 0: case WIDTH-1: // At the first and last coloum, place vertical lines at every row
                layout[y_row][x_col] = v_line;
            }
        }
    }
    layout[16][4] = charging; // Drop off is hardcoded to be at this spot
    layout[16][31] = drop_off; // Charging station is hardcoded to be at this spot
}

void print_array(int layout[HEIGHT][WIDTH]) {


    for (int y_row = 0; y_row < HEIGHT; ++y_row) // Looping through all the rows in the layout array
    {


        for (int x_col = 0; x_col < WIDTH; ++x_col) // Looping through all the coloumns in the layout array
        {
            switch (layout[y_row][x_col])
            {
                case vacant: printf("  "); break; // If the element is vacant, print a blank space " "

                case v_line: printf("| "); break; // If the element is v_line , print a vertical line "|"

                case h_line: printf("--"); break; // If the element is h_line , print a  horizontal line "-"

                case robot: printf("O "); break; // If the element is robot , print a "O"

                case shelf: printf("X "); break; // If the element is shelf , print a "X"

                case drop_off: printf("D "); break; // If the element is drop_off , print a "D"

                case charging: printf("C "); break; // If the element is charging , print a "C"

                case path_enum: printf("* "); break;
            }
        }
        printf("\n"); // Go to the next row with a new-line
    }
}





static bool verti = false;
void print_num_array(int layout[HEIGHT][WIDTH]) {

    static bool Hori = true;
    if (Hori) {
        horizontal_num();
        Hori=false;
    }

    for (int y_row = 0; y_row < HEIGHT; ++y_row) // Looping through all the rows in the layout array
    {
        if (!verti) {
            vertical_num(y_row);
        }

        for (int x_col = 0; x_col < WIDTH; ++x_col) // Looping through all the coloumns in the layout array
        {
            switch (layout[y_row][x_col])
            {
                case vacant: printf("  "); break; // If the element is vacant, print a blank space " "

                case v_line: printf("| "); break; // If the element is v_line , print a vertical line "|"

                case h_line: printf("--"); break; // If the element is h_line , print a  horizontal line "-"

                case robot: printf("O "); break; // If the element is robot , print a "O"

                case shelf: printf("X "); break; // If the element is shelf , print a "X"

                case drop_off: printf("D "); break; // If the element is drop_off , print a "D"

                case charging: printf("C "); break; // If the element is charging , print a "C"

                case path_enum: printf("* "); break;
            }
        }
        printf("\n"); // Go to the next row with a new-line
    }
    verti=true;
}