#include "dynamic_warehouse.h"
#include <stdio.h>
#include <stdlib.h>
#include "../managers/array_manager.h"

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_RESET "\x1b[0m"

char* mLayout = NULL;
int* mDimensions = NULL;

void setHegihtWidth(
    int* height, int* width, int* yShelfSections, int* yShelfDivider, int* xShelfWidth, int* sectionWidth) {

    //int yShelfSections, xShelfSections, xShelfWidth, xShelfDivider, yShelfDivider;

    // Variables for custom layout
    int xShelfDivider, xShelfSections;

    do {
        printf("Enter the following:\n"
               " - Shelf sections (y-axis).\n"
               " - Space between vertical sections (y axis).\n"
               " - Shelf sections (x-axis).\n"
               " - Shelf width (x-axis).\n"
               " - Space between horizontal sections (x axis).\n"
               "Give 5 inputs and separate each by a space ' '. \n"
               "User Inputs: ");

        scanf("%i %i %i %i %i", yShelfSections, yShelfDivider, &xShelfSections, xShelfWidth, &xShelfDivider);


        // Calculates warehouse dimensions
        // sectionWidth is the width of one shelf + the walking space between that and the next shelf
        *sectionWidth = (*xShelfWidth + xShelfDivider);

        // Total Width of the warehouse minus one xShelfDivider
        // to ensure shelves leve no walking space against the warehouse wall.
        const int warehouseWidth = (*xShelfWidth + xShelfDivider) * xShelfSections - xShelfDivider;

        // Total Height of the warehouse. Each section is defined of 2 shelve rows and x empty rows.
        const int warehouseHeight = (*yShelfSections * (2 + *yShelfDivider));

        // 6 for bottom lines (where docking and packing station is and end wall)
        *height = warehouseHeight + 4 + 2;

        // Adding the widtch of the v_lines
        *width = warehouseWidth + 2;

        // Setting minimum size, to ensure a functional layout
        if (*yShelfSections < 0 || xShelfSections < 0 || xShelfSections * (*xShelfWidth + xShelfDivider) <= 10) {
            printf(ANSI_COLOR_RED "The combined length of ---> x-sections * (shelf width + shelf between sections),"
                                  " should be greater than 10 (9 if counting from 0)" ANSI_COLOR_RESET"\n");
        };

        // Ensuring that the layout is not getting out of bounds
        if (*width >= 200 || *height >= 200) {
            printf(ANSI_COLOR_RED "The combined Width and Height exceeds the max of 200x200" ANSI_COLOR_RESET"\n");
        };

    // Input validation
    } while (*yShelfSections < 0 || xShelfSections < 0 || (xShelfSections * (*xShelfWidth + xShelfDivider)) <= 10
        || *height >= 200 || *width >= 200); // has ot have 1 section on y-axis and if x-axis is less than 10
}


void dynamicWarehouseDesign(int height, int width, int layout[height][width], node* charging_station,
    node* dropoff_point, int yShelfSections, int yShelfDivider, int xShelfWidth, int sectionWidth) {
    
    // Creates a 1D of the warehouse
    int mLayout[height*width];

    // Sets layout to vacant
    for (int i = 0; i < (height * width); i++) {
        mLayout[i] = vacant;
    }

    // This is where we create the warehouse layout based on the values given earlier.
    int currentLength = 0;
    int currentRow = 1;

    // Running through the sections of shelves and setting its values
    for (int section_count = 0; section_count < yShelfSections; section_count++) {

        // Creates empty rows of walking space above the shelf section
        for (int row = 0; row < yShelfDivider; row++, currentRow++) {
            for (int col = 0; col < width; col++) {
                mLayout[currentRow * width + col] = vacant;
            }
        }
        // Creates 2 rows with shelves and x cols of divider space
        for (int row = 0; row < 2; row++, currentRow++) {
            currentLength = 0;

            // Creating the shelf sections
            for (int col = 1; col < width-1; col++) {
                if (currentLength < xShelfWidth) { // If currentLength in less then the length of a shelf section it places a shelf
                        mLayout[currentRow * width + col] = shelf;

                } else {
                    mLayout[currentRow * width + col] = vacant; // If it's larger that xShelfWidth it will place a space

                }
                currentLength++;
                if (currentLength >= sectionWidth) currentLength = 0; // If the width is equal to or larger than a section width it will reset
            }
        }
    }


    // Creates the boundary of the warehouse for the 2D array and mLayout in memory
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            if (row == 0 || row == height-1) {
                if (col == 0 || col == width-1) {
                    mLayout[row * width + col] = v_line;
                } else {
                    mLayout[row * width + col] = h_line;
                }
            }
            if (col == 0 || col == width-1) {
                mLayout[row * width + col] = v_line;

            }
        }
    }

    // Defining charging station position
    int stationRow = height - 3;
    mLayout[stationRow * width + 4] = charging;

    *charging_station = (node){stationRow, 4};

    // Defining drop-off position
    mLayout[stationRow * width + (width - 5)] = drop_off;

    *dropoff_point = (node){stationRow, width - 5};
    
    // Copy 1D array to 2D array
    int rowCounter = 0;
    int colCounter = 0;
    for (int i = 0; i < height * width; i++) {
        if (colCounter == width-1) {
            layout[rowCounter][colCounter] = mLayout[rowCounter * width + colCounter];
            colCounter = 0;
            rowCounter++;
        } else {
            layout[rowCounter][colCounter] = mLayout[rowCounter * width + colCounter];
            colCounter++;
        }
    }
}