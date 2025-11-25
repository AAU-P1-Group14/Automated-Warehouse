#include "dynamic_warehouse.h"
#include <stdio.h>
#include <stdlib.h>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_RESET "\x1b[0m"

char* mLayout = NULL;
int* mDimensions = NULL;

int dynamicWarehouseDesign() {
    int yShelfSections, xShelfSections, xShelfWidth, xShelfDivider, yShelfDivider;

    do {
        printf("Enter the following:\n"
               " - Shelf sections (y-axis).\n"
               " - Space between vertical sections (y axis).\n"
               " - Shelf sections (x-axis).\n"
               " - Shelf width (x-axis).\n"
               " - Space between horizontal sections (x axis).\n"
               "Give 5 inputs and separate each by a space ' '. \n"
               "User Inputs: ");

        scanf("%i %i %i %i %i", &yShelfSections, &yShelfDivider, &xShelfSections, &xShelfWidth, &xShelfDivider);

        if (yShelfSections < 0 || xShelfSections < 0 || xShelfSections * (xShelfWidth + xShelfDivider) <= 10) {
                printf(ANSI_COLOR_RED "The combined length of ---> x-sections * (shelf width + shelf between sections), should be greater than 10 (9 if counting from 0)" ANSI_COLOR_RESET"\n");
            };

    } while (yShelfSections < 0 || xShelfSections < 0 || (xShelfSections * (xShelfWidth + xShelfDivider)) <= 10); // has ot have 1 section on y-axis and if x-axis is less than 10

    // Calculates warehouse dimensions
    const int sectionWidth = (xShelfWidth + xShelfDivider); // sectionWidth is the width of one shelf + the walking space between that and the next shelf
    const int warehouseWidth = (xShelfWidth + xShelfDivider) * xShelfSections - xShelfDivider; // Total Width of the warehouse minus one xShelfDivider to ensure shelves leve no walking space against the warehouse wall.
    const int warehouseHeight = (yShelfSections * (2 + yShelfDivider)); // Total Height of the warehouse. Each section is defined of 2 shelve rows and x empty rows.

    int rows = warehouseHeight + 4 + 2; // 5 for bottom lines (where docking and packing station is and end wall)
    int cols = warehouseWidth + 2;


    // Creates memory for the warehouse and fills all of it with dots
    mLayout = malloc(rows * cols * sizeof(char)); // Assigns memory to store the memory in
    for (int i = 0; i < (rows * cols); i++) {
        mLayout[i] = ' ';
    }
    // Creates memory and assigns rows and cols within it
    mDimensions = malloc(2 * sizeof(int));
    mDimensions[0] = rows;
    mDimensions[1] = cols;


    // Creates an array for the layout to be stored in.
    char layoutArr[rows][cols];
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            layoutArr[row][col] = ' ';
        }
    }


    // This is where we create the warehouse layout based on the values given earlier.
    int currentLength = 0;
    int currentRow = 1;
    for (int height = 0; height < yShelfSections; height++) {
        for (int row = 0; row < yShelfDivider; row++, currentRow++) { // Creates x empty rows of walking space
            for (int col = 0; col < cols; col++) {
                mLayout[currentRow * cols + col] = ' ';
                layoutArr[currentRow][col] = ' ';
            }
        }
        // Creates 2 rows with shelves and x cols of divider space
        for (int row = 0; row < 2; row++, currentRow++) {
            currentLength = 0;

            for (int col = 1; col < cols-1; col++) {
                if (currentLength < xShelfWidth) { // If currentLength in less then the length of a shelf section it places a shelf
                        mLayout[currentRow * cols + col] = 'x';
                        layoutArr[currentRow][col] = 'x';

                } else {
                    mLayout[currentRow * cols + col] = ' '; // If it's larger that xShelfWidth it will place a space
                    layoutArr[currentRow][col] = ' ';

                }
                currentLength++;
                if (currentLength >= sectionWidth) currentLength = 0; // If the width is equal to or larger than a section width it will reset
            }
        }
    }


    // Creates the boundary of the warehouse for the 2D array and mLayout in memory
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (row == 0 || row == rows-1) {
                if (col == 0 || col == cols-1) {
                    layoutArr[row][col] = '|';
                    mLayout[row * cols + col] = '|';
                } else {
                    layoutArr[row][col] = '-';
                    mLayout[row * cols + col] = '-';
                }
            }
            if (col == 0 || col == cols-1) {
                layoutArr[row][col] = '|';
                mLayout[row * cols + col] = '|';

            }
        }
    }


    int stationRow = rows - 3;
    layoutArr[stationRow][4] = 'C';
    mLayout[stationRow * cols + 4] = 'C';

    layoutArr[stationRow][cols - 5] = 'D';
    mLayout[stationRow * cols + (cols - 5)] = 'D';


    //Create 2D array from 1D array in malloc

    char newarraytest[rows][cols];
    int rowCounter = 0;
    int colCounter = 0;
    for (int i = 0; i < rows * cols; i++) {
        if (colCounter == cols-1) {
            newarraytest[rowCounter][colCounter] = mLayout[rowCounter * cols + colCounter];
            colCounter = 0;
            rowCounter++;
        } else {
            newarraytest[rowCounter][colCounter] = mLayout[rowCounter * cols + colCounter];
            colCounter++;
        }
    }

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            printf("%c", newarraytest[row][col]);
        }
        printf("\n");
    }


 /*
    // Prints the layout from memory
    int colCounter = 0;
    for (int i = 0; i < rows * cols; i++) {
        if (colCounter == cols) {
            colCounter = 0;
            printf("\n");
            printf("%c", mLayout[i]);
            colCounter++;
        } else {
            printf("%c", mLayout[i]);
            colCounter++;
        }
    }

    /*
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (layoutArr[row][col] == '-' || layoutArr[row][col] == '|') {
                printf(ANSI_COLOR_RED "%c" ANSI_COLOR_RESET, layoutArr[row][col]);
            }
            else if (layoutArr[row][col] == 'x') {
                printf(ANSI_COLOR_GREEN "%c" ANSI_COLOR_RESET, layoutArr[row][col]);
            }
            else if (layoutArr[row][col] == 'C' ||layoutArr[row][col] == 'D') {
                printf(ANSI_COLOR_BLUE "%c" ANSI_COLOR_RESET, layoutArr[row][col]);
            }
            else {
                printf("%c", layoutArr[row][col]);
            }
        }
        printf("\n");
    } */
}