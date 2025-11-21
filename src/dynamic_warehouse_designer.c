#include "dynamic_warehouse_designer.h"
int dynamicWarehouseDesign() {

    int verticalShelfSections, horizontalShelfSections, horizontalShelfWidth, horisontalShelfSpace, verticalShelfSpace;
    int shelveSectionLen = 0;
    int row = 0;

    do {
    // The height of the warehouse
    printf("Vertical shelf sections: ");
    scanf("%i", &verticalShelfSections);
    // The space between shelves vertically
    printf("Space between vertical shelves: ");
    scanf("%i", &verticalShelfSpace);
    // How many section you want horizontally
    printf("Horizontal shelf sections: ");
    scanf("%i", &horizontalShelfSections);
    // How width each shelf is horizontally (the length of them)
    printf("Horizontal shelf width: ");
    scanf("%i", &horizontalShelfWidth);
    // Width between 2 shelves
    printf("Walking space between horizontal shelve sections: ");
    scanf("%i", &horisontalShelfSpace);
    } while (verticalShelfSections < 1 && horizontalShelfSections < 1 && horizontalShelfWidth <= 1 && horisontalShelfSpace <= 1);

    // Combined width of one section (shelve width + space to the next one)
    int sectionWidth = (horizontalShelfWidth + horisontalShelfSpace);
    // Total Width of the warehouse minus one horisontalShelveSpace to ensure shelves leve no walking space agains the warehouse wall.
    int totalWidth = (horizontalShelfWidth + horisontalShelfSpace) * horizontalShelfSections - horisontalShelfSpace;
    // Total Height of the warehouse. Each section is defined of 2 empty rows and 2 shelve rows. This means each section = 4 rows
    int totalHeight = (verticalShelfSections * (2+verticalShelfSpace));
    // 2D array to store the warehouse layout in.
    char layout[totalHeight+4][totalWidth]; // Creates a 2d array to store the warehouse layout in

    // Nested for-loops to create a warehouse layout
    for (int height = 0; height < verticalShelfSections; height++) {
        // Creates 2 rows that are empty based on the totalWidth
        for (int x = 0; x < verticalShelfSpace; x++, row++) {
            for (int y = 0; y < totalWidth; y++) {
                layout[row][y] = ' ';
            }
        }
        // Creates 2 rows with shelves and space
        for (int x = 0; x < 2; x++, row++) {
            shelveSectionLen = 0;
            // As long as curShelveLen in less than the defined length of a shelf it will place a shelf
            for (int y = 0; y < totalWidth; y++) {
                if (shelveSectionLen < horizontalShelfWidth) {
                    layout[row][y] = 'x';

                } else { // If it's not less that horizontalShelveWidth it will place a space
                    layout[row][y] = ' ';
                }
                shelveSectionLen++;
                // If the shelveSectionLen is equal to or larger than a section width it will reset
                if (shelveSectionLen >= sectionWidth) {
                    shelveSectionLen = 0;
                }
            }
        }
    }

    // Loop to create the bottom 4 rows with a charling station (C) and docktion station (D)
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < totalWidth; y++) {
            layout[row][y] = ' ';
        }
        // Manually inserts Charging and Docking station with fixed positions in the dynamic array
        layout[totalHeight+2][3] = 'C';
        layout[totalHeight+2][totalWidth-4] = 'D';
        row++;
    }

    // Prints top line of the warehouse
    printf(" "); // Spacing
    for (int topWall = 0; topWall < totalWidth; topWall++) {
        printf("_");
    }
    printf("\n");

    // Prints each element in the 2D array
    for (int i = 0; i < totalHeight+4; i++) {
        // Prints the left wall
        printf("|");
        // Prints items in the array
        for (int j = 0; j < totalWidth; j++) {
            printf("%c",layout[i][j]);
        }
        // Prints the right wall and a line counter
        printf("|%i", i+1); // Remember to subtract 1 from the actual coordinate calculation
        // Prints a new line for the next row in the array
        printf("\n");
    }

    // Prints the bottom wall of the warehouse
    printf(" "); // Creates space
    for (int bottomLine = 0; bottomLine < totalWidth/5; bottomLine++) {
        // Loop to print '-' and then insert a 5 as a visual representation of where you are
        for (int x = 0; x < 4; x++) {
            printf("-");
        }
        printf("5");
    }
}