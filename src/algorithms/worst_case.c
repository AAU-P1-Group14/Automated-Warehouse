#include "worst_case.h"

int worst_case(int layout[HEIGHT][WIDTH], node target, node dropoff, node position) {
    enum momentum {up, down, left, right};
    int found_target = 0;
    int found_dropoff = 0;
    int iterations = 0;
    int tiles = 0;

    while (iterations < 100000 && !(found_dropoff && found_target)) {
        iterations++;
        //printf("Iteration: %d\n", iterations);
        //printf("Tiles: %d\n", tiles);
        move_position(layout, &position, &tiles);
        update_and_check(layout, target, dropoff, position, &found_target, &found_dropoff);
    }
    if (found_target && found_dropoff) return tiles;
    else return 0;
}

void move_position(int layout[HEIGHT][WIDTH], node* position, int* tiles) {
    int random_direction = rand() % 4;

    switch (random_direction) {
    case 0:
        if (layout[position->y][position->x - 1] != v_line &&
            layout[position->y][position->x - 1] != shelf) {
            position->x--;
            (*tiles)++;
        }
        break;

    case 1:
        if (layout[position->y + 1][position->x] != h_line &&
            layout[position->y + 1][position->x] != shelf) {
            position->y++;
            (*tiles)++;
        }
        break;

    case 2:
        if (layout[position->y - 1][position->x] != h_line &&
            layout[position->y - 1][position->x] != shelf) {
            position->y--;
            (*tiles)++;
        }
        break;

    case 3:
        if (layout[position->y][position->x + 1] != v_line &&
            layout[position->y][position->x + 1] != shelf) {
            position->x++;
            (*tiles)++;
        }
        break;
    }
}

void update_and_check(int layout[HEIGHT][WIDTH], node target, node dropoff, node position, int* found_target, int* found_dropoff) {
    if (position.y != target.y || position.x != target.x){
        if (position.y != dropoff.y || position.x != dropoff.x) {
            if (position.y != 16 || position.x != 4){
                layout[position.y][position.x] = path_enum;
            }
        }
    }

    if (!(*found_target)) {
        check_if_target(layout, target, position, found_target);
    }

    if (*found_target && !(*found_dropoff)) {
        check_if_dropoff(layout, dropoff, position, found_dropoff);
    }

}

void check_if_target(int layout[HEIGHT][WIDTH], node target, node position, int* found_target) {
    int dRow[] = { -1, 0, 1, 0 };
    int dCol[] = { 0, 1, 0, -1 };
    for (int i = 0; i < 4; i++) {
        node adj = {position.y + dRow[i], position.x + dCol[i]};
        if (adj.y == target.y && adj.x == target.x) {
            *found_target = 1;
        }
    }

}

void check_if_dropoff(int layout[HEIGHT][WIDTH], node dropoff, node position, int* found_dropoff) {
    int dRow[] = { -1, 0, 1, 0 };
    int dCol[] = { 0, 1, 0, -1 };
    for (int i = 0; i < 4; i++) {
        node adj = {position.y + dRow[i], position.x + dCol[i]};
        if (adj.y == dropoff.y && adj.x == dropoff.x) {
            *found_dropoff = 1;
        }
    }
}