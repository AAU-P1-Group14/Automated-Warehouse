#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "types.h"

//Get array length, return the number of elements in a static array.
#define LEN(arr) (sizeof(arr) / sizeof((arr)[0]))

//Find max/min value in an array.
int max_int(const int *array, const int size) {
    int max = array[0];

    for (int i = 0; i < size; i++) {
        if (array[i] > max) {
            max = array[i];
        }
    }

    return max;
}

double max_double(const double *array, const int size) {
    double max = array[0];

    for (int i = 0; i < size; i++) {
        if (array[i] > max) {
            max = array[i];
        }
    }

    return max;
}

//Reverse an array in place.

//Sum all elements in an array.
int sum_ints(const int *array, const int size) {
    int sum = 0;

    for (int i = 0; i < size; i++) {
        sum += array[i];
    }

    return sum;
}

double sum_doubles(const double *array, const int size) {
    double sum = 0;

    for (int i = 0; i < size; i++) {
        sum += array[i];
    }

    return sum;
}

//Compute average of array elements.
int int_avr(const int *array, const int size) {
    return sum_ints(array, size) / size;
}

double double_avr(const double *array, const int size) {
    return sum_doubles(array, size) / size;
}

//Count occurrences of a specific value in an array.
int array_occur(const void *array, const void *target, const int size, int elem_size, int (*compare)(const void *, const void *)) {
    int sum = 0;

    //The reason as to why we do this here, is we convert it into a pointer that points
    //to a single byte, this will be used later, as when you step along in raw memory, you step by bytes
    //More basically said, arr becomes a pointer to the first byte at the same location that array points to
    const unsigned char *arr = array;
    for (int i = 0; i < size; i++) {
        //So we start at the pointer to the byte we found ealier, then we move
        //i * sie of the elements bytes forward to find the start of i-th element
        const void *current = arr + i * elem_size;
        if (compare(current, target)) {
            sum++;
        }
    }

    return sum;
}

//Rotate array elements left or right by one.

//Copy an array into another.

//Check if an array is sorted (ascending or descending).

//Find index of a value in an array (return -1 if not found).
int get_index(const void *array, const void *target, const int size, int elem_size, int (*compare)(const void *, const void *)) {
    const unsigned char *arr = array;
    for (int i = 0; i < size; i++) {
        const void *current = arr + i * elem_size;
        if (compare(current, target) == 0) {
            return i;
        }
    }
    return -1;
}

//------------ MISC HELP FUNCS -------------
int cmp_int(const void *a, const void *b) {
    int x = *(const int *)a, y = *(const int *)b;
    return (x > y) - (x < y);
}

int cmp_double(const void *a, const void *b) {
    double x = *(const double *)a, y = *(const double *)b;
    return (x > y) - (x < y);
}

int cmp_string(const void *a, const void *b) {
    const char *x = *(const char **)a;
    const char *y = *(const char **)b;
    return strcmp(x, y);
}

int cmp_node(node a, node b) {
    return a.x == b.x && a.y == b.y;
}

// Function to clear the terminal/console from previous outputs
void clear_screen(void) {
    /* 1) ANSI escape-koder (virker i mange moderne terminaler) */
    printf("\033[2J\033[H");
    fflush(stdout);

    /* 2) system("cls") – klassisk Windows cmd/powershell */
    system("cls");

    /* 3) system("clear") – hvis nogen kører via fx Git Bash eller WSL */
    system("clear");

    /* 4) conio.h's clrscr() – KUN hvis I rent faktisk har conio.h */
    /* clrscr(); */
}