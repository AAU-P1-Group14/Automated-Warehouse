#include "worst_case.h"

int worst_case(int layout[HEIGHT][WIDTH], node target, node position) {
    enum momentum {up, down, left, right};
    int found_target = 0;
    int found_dropoff = 0;
    int momentum = left;
    int iterations = 0;

    while (iterations < 1000 || (found_dropoff && found_target)) {
        iterations++;
        if (momentum == left) {
            if (layout[position.y][position.x - 1] != h_line && layout[position.y][position.x - 1] != shelf) {
                position.x--;
                update_and_check(layout, target, position, &found_target, &found_dropoff);
            }
            else {
                if (layout[position.y + 1][position.x] != v_line && layout[position.y + 1][position.x] != shelf) {
                    position.y++;
                    momentum = up;
                    update_and_check(layout, target, position, &found_target, &found_dropoff);
                }
            }
        }
    }

    return found_target && found_dropoff;
}

void update_and_check(int layout[HEIGHT][WIDTH], node target, node position, int* found_target, int* found_dropoff) {
    if (position.y != target.y && position.x != target.x){
        layout[position.y][position.x] = path_enum;
    }

    if (!(*found_target)) {
        check_if_target(layout, target, position, found_target);
    }

    if (*found_target && !(*found_dropoff)) {
        check_if_dropoff(layout, target, position, found_dropoff);
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