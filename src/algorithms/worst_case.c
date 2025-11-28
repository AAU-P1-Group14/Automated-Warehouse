#include "worst_case.h"

int worst_case(int height, int width, int layout[height][width], node target, node dropoff, node charging, node position) {
    int found_target = false;
    int found_dropoff = false;
    int iterations = 0;
    int tiles = 0;

    while (iterations < 100000 && !(found_dropoff && found_target)) {
        iterations++;
        // Move the robot
        move_position(height, width, layout, &position, &tiles);
        // Update the layout and check if target or dropoff is found
        update_and_check(height, width, layout, target, dropoff, charging, position, &found_target, &found_dropoff);
    }
    if (found_target && found_dropoff) return tiles;
    return 0;
}

void move_position(int height, int width, int layout[height][width], node* position, int* tiles) {
    // Create a random number in interval [0, 1, 2, 3]
    int random_direction = rand() % 4;

    switch (random_direction) {
        // Move left
        case 0:
            if (layout[position->y][position->x - 1] != v_line &&
                layout[position->y][position->x - 1] != shelf) {
                position->x--;
                (*tiles)++;
            }
            break;

        // Move up
        case 1:
            if (layout[position->y + 1][position->x] != h_line &&
                layout[position->y + 1][position->x] != shelf) {
                position->y++;
                (*tiles)++;
            }
            break;

        // Move down
        case 2:
            if (layout[position->y - 1][position->x] != h_line &&
                layout[position->y - 1][position->x] != shelf) {
                position->y--;
                (*tiles)++;
            }
            break;

        // Move right
        case 3:
            if (layout[position->y][position->x + 1] != v_line &&
                layout[position->y][position->x + 1] != shelf) {
                position->x++;
                (*tiles)++;
            }
            break;
        }
}

void update_and_check(int height, int width, int layout[height][width], node target, node dropoff, node charging, node position, int* found_target, int* found_dropoff) {
    if ((position.y != target.y || position.x != target.x) &&
        (position.y != dropoff.y || position.x != dropoff.x) &&
        (position.y != charging.y || position.x != charging.x)) {
        // Update layout if position is not target, dropoff or charging station
        layout[position.y][position.x] = path_enum;
    }

    // If target is not found, check if target is here
    if (!(*found_target)) {
        check_for_adjecent(height, width, layout, target, position, found_target);
    }

    // If target is found but drop-off is not found, check if drop-off is here
    if (*found_target && !(*found_dropoff)) {
        check_for_adjecent(height, width, layout, dropoff, position, found_dropoff);
    }

}

void check_for_adjecent(int height, int width, int layout[height][width], node check_cell, node position, int* boolean_argument) {
    // Check adjecent cells if drop-off is here
    int dRow[] = { -1, 0, 1, 0 };
    int dCol[] = { 0, 1, 0, -1 };
    for (int i = 0; i < 4; i++) {
        node adj = {position.y + dRow[i], position.x + dCol[i]};
        if (adj.y == check_cell.y && adj.x == check_cell.x) {
            *boolean_argument = true;
        }
    }
}