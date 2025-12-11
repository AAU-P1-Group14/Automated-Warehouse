#include "array_manager.h"
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define BLUE    "\x1b[34m"
#define COLOR_RESET   "\x1b[0m"
#define YELLOW "\x1b[33m"
#define GREY "\x1b[90m"


void horizontal_num(int width) {
    bool first = true;  // we make a bool
    for (int i = 0; i < width; i++) { // Looping through all the coloumns in the layout array
        if (i % 5 == 0) { //we only want every 5 number, because there wouldn't be room.
            if (first) {
                printf("  %d         ", i);
                first = false;     //we use the bool here to format the first number ie 0 properly
            } else {
                if (i > 9 && i<100)     // then every other number will be printed differently depending on
                    printf(" %d       ", i); // whether they are above or below 9
                else if (i < 9)
                    printf("%d       ", i);
                } if (i>=100) {
                    printf(" %d      ", i);
                }
            }
        }
    printf("\n");  //also make a new line that the numbers can actually be on
}

void vertical_num(const int y_row) {  // the vertical numbers are far more simple. we have y_row as parameter
    if (y_row < 10) {            // then for each time we go down we print the next number
        printf("%d  ", y_row);  //if its below 10 we add a space for formatting
    } else if (y_row >= 10 && y_row < 100) {
        printf("%d ", y_row);
    } if (y_row >=100) {
        printf("%d"  , y_row);
    }

}

void init_array(int height, int width, int layout[height][width]) {

    for (int y_row = 0; y_row < height; ++y_row) // Looping through all the rows in the layout array
    {
        for (int x_col = 0; x_col < width; ++x_col) // Looping through all the coloumns in the layout array
        {
            // Setting all positions to vacant
            layout[y_row][x_col] = vacant;

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

            case 0: case 18: // At the first and last row, place horizontal lines at every coloum (18: end of layout)
                layout[y_row][x_col] = h_line;
            }
            switch (x_col)
            {
                case 0: case 35: // At the first and last coloum, place vertical lines at every row (35: end of layout)
                layout[y_row][x_col] = v_line;
            }
        }
    }
    layout[16][4] = charging; // Drop off is hardcoded to be at this spot
    layout[16][31] = drop_off; // Charging station is hardcoded to be at this spot
}

void print_array(int height, int width, int layout[height][width], bool print_num) {

    if (print_num)
        horizontal_num(width);

    for (int y_row = 0; y_row < height; ++y_row) // Looping through all the rows in the layout array
    {
        if (print_num)
            vertical_num(y_row);

        for (int x_col = 0; x_col < width; ++x_col) // Looping through all the coloumns in the layout array
        {
            switch (layout[y_row][x_col])
            {
                case vacant: printf("  "); break; // If the element is vacant, print a blank space " "

                case v_line: printf("🧱"); break; // If the element is v_line, print a vertical line "|"

                case h_line: printf("🧱"); break; // If the element is h_line, print a  horizontal line "-"

                case robot: printf("🤖"); break; // If the element is robot, print a "O"

                case shelf: printf("🗄️"); break; // If the element is shelf, print a "X"

                case drop_off: printf( "📍" ); break; // If the element is drop_off, print a "D"

                case charging: printf(BLUE "🔋" COLOR_RESET); break; // If the element is charging, print a "C"

                case path_enum: printf("🔸"); break; // If the element is on the path, print a "*"

                case target: printf( "📦" ); break; // If the element is a target, print a "T"

                default: printf("? "); break; // If the element is undefined, print a "?"
            }
        }
        printf("\n"); // Go to the next row with a new-line
    }
}


void clear_path(int height, int width, int layout[height][width],
    node path[height * width], int* tiles, node target_t) {

    // Reset layout array
    // Clear path in layout array and clear path node array
    for (int i = 0; i < *tiles; ++i)
    {

        if (layout[path[i].y][path[i].x] != charging && layout[path[i].y][path[i].x] != drop_off) {
            layout[path[i].y][path[i].x] = vacant;
            path[i].y = 0;
            path[i].x = 0;
        }
    }

    layout[target_t.y][target_t.x] = shelf;

    *tiles = 0;

}

void force_clear_path(int height, int width, int layout[height][width]) {
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            if (layout[row][col] == path_enum) layout[row][col] = vacant;
            if (layout[row][col] == target) layout[row][col] = shelf;
        }
    }
}