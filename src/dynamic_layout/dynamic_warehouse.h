#ifndef AUTOMATED_WAREHOUSE_DYNAMIC_WAREHOUSE_H
#define AUTOMATED_WAREHOUSE_DYNAMIC_WAREHOUSE_H

#include <stdio.h>
#include <stdlib.h>
#include "../utility/types.h"
#include "../managers/array_manager.h"

extern char* mLayout;
extern int* mDimensions;

void dynamicWarehouseDesign(int height, int width, int layout[height][width], node* charging_station, node* dropoff_point, int yShelfSections, int yShelfDivider, int xShelfWidth, int sectionWidth);

void setHegihtWidth(int* height, int* width, int* yShelfSections, int* yShelfDivider, int* xShelfWidth, int* sectionWidth);

#endif //AUTOMATED_WAREHOUSE_DYNAMIC_WAREHOUSE_H

/*
void setHegihtWidtt(int* height, int* width, int* yShelfSections, int* yShelfDivider, int* xShelfWidth, int* sectionWidth) {

    //int yShelfSections, xShelfSections, xShelfWidth, xShelfDivider, yShelfDivider;

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

        if (*yShelfSections < 0 || xShelfSections < 0 || xShelfSections * (*xShelfWidth + xShelfDivider) <= 10) {
            printf(ANSI_COLOR_RED "The combined length of ---> x-sections * (shelf width + shelf between sections), should be greater than 10 (9 if counting from 0)" ANSI_COLOR_RESET"\n");
        };

    } while (*yShelfSections < 0 || xShelfSections < 0 || (xShelfSections * (*xShelfWidth + xShelfDivider)) <= 10); // has ot have 1 section on y-axis and if x-axis is less than 10

    // Calculates warehouse dimensions
    *sectionWidth = (*xShelfWidth + xShelfDivider); // sectionWidth is the width of one shelf + the walking space between that and the next shelf
    const int warehouseWidth = (*xShelfWidth + xShelfDivider) * xShelfSections - xShelfDivider; // Total Width of the warehouse minus one xShelfDivider to ensure shelves leve no walking space against the warehouse wall.
    const int warehouseHeight = (*yShelfSections * (2 + *yShelfDivider)); // Total Height of the warehouse. Each section is defined of 2 shelve rows and x empty rows.

    *height = warehouseHeight + 4 + 2; // 5 for bottom lines (where docking and packing station is and end wall)
    *width = warehouseWidth + 2;

*/