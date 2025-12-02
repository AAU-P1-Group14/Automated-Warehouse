#include "misc.h"

int cmp_node(node a, node b) {
    return a.x == b.x && a.y == b.y;
}

// Function to clear the terminal/console from previous outputs
void clear_terminal(void) {
    #ifdef _WIN32
        system("cls");    // Good OS (Windows)
    #else
        system("clear");  // Bad OS (Mac)
    #endif

    // Fallback: Spam new lines
    for (int i = 0; i < 50; ++i) {
        printf("\n");
    }
}