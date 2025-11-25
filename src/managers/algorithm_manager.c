#include "algorithm_manager.h"

void run_algorithms(int layout[HEIGHT][WIDTH], node target_t, int bench, bool procedural, bool debug) {
    // Creating array that contains coordinates of the robot path
    static node path[HEIGHT * WIDTH];

    if (!procedural) printf("TARGET SHELF: (%d, %d)\n", target_t.y, target_t.x);
    else printf("TARGET SHELF: PROCEDURAL\n");
    printf("BENCHES: (%d)\n\n", bench);
    for (int i = 0; i < 2; i++) {

        // Input target in layout array
        layout[target_t.y][target_t.x] = target;

        struct timespec timestamp1;
        struct timespec timestamp2;

        int tiles_bfs = 0;
        int tiles_dfs = 0;

        node targets[bench];
        if (procedural) {
            for (int i = 0; i < bench; i++) {
                targets[i] = random_target(layout);
            }
        }

        switch (i) {
            case 0:
                int bfs_valid = bfs(layout, target_t, (node){16, 4}, &tiles_bfs, path, true);
                if (!bfs_valid) {
                    continue;
                }

                bfs_valid = bfs(layout, (node){16, 31}, target_t, &tiles_bfs, path, true);
                if (!bfs_valid) {
                    continue;
                }

                if (procedural) {
                    clock_gettime(CLOCK_REALTIME, &timestamp1);

                    for (int i = 0; i < bench; i++) {
                        // BFS Path finding algorithm, adding the path from charging station to target
                        bfs(layout, targets[i], (node){16, 4}, &tiles_bfs, path, false);

                        // BFS Path finding algorithm, adding the path from target station to drop-off
                        bfs(layout, (node){16, 31}, targets[i], &tiles_bfs, path, false);
                    }

                } else {
                    clock_gettime(CLOCK_REALTIME, &timestamp1);

                    for (int i = 0; i < bench; i++) {
                        // BFS Path finding algorithm, adding the path from charging station to target
                        bfs(layout, target_t, (node){16, 4}, &tiles_bfs, path, false);

                        // BFS Path finding algorithm, adding the path from target station to drop-off
                        bfs(layout, (node){16, 31}, target_t, &tiles_bfs, path, false);
                    }
                }

                clock_gettime(CLOCK_REALTIME, &timestamp2);
                long long current = timestamp1.tv_sec * 1000000LL + timestamp1.tv_nsec / 1000;
                long long passed = timestamp2.tv_sec * 1000000LL + timestamp2.tv_nsec / 1000;

                long long passtime = passed - current;

                // Print out the result from BFS
                printf("BFS algorithm:\n");
                print_array(layout, false);
                printf("\nFinal route for BFS was %d tiles\n\n", tiles_bfs);
                printf("Total benches for BFS took %lld micros\n", passtime);
                printf("Average route for BFS took %lld micros\n\n\n", passtime/bench);

                //Clears the path from the layout array
                if (procedural) clear_path(layout, path, &tiles_bfs, targets[0]);
                clear_path(layout, path, &tiles_bfs, target_t);

                break;
            case 1:
                int dfs_valid = dfs(layout, target_t, (node){16, 4}, &tiles_dfs, true);
                if (!dfs_valid) {
                    continue;
                }

                dfs_valid = dfs(layout, (node){16, 31}, target_t, &tiles_dfs, true);
                if (!dfs_valid) {
                    continue;
                }

                if (procedural) {
                    clock_gettime(CLOCK_REALTIME, &timestamp1);

                    for (int i = 0; i < bench; i++) {
                        // DFS Path finding algorithm, adding the path from charging station to target
                        dfs(layout, targets[i], (node){16, 4}, &tiles_dfs, false);

                        // DFS Path finding algorithm, adding the path from target station to drop-off
                        dfs(layout, (node){16, 31}, targets[i], &tiles_dfs, false);
                    }

                } else {
                    clock_gettime(CLOCK_REALTIME, &timestamp1);

                    for (int i = 0; i < bench; i++) {
                        // DFS Path finding algorithm, adding the path from charging station to target
                        dfs(layout, target_t, (node){16, 4}, &tiles_dfs, false);

                        // DFS Path finding algorithm, adding the path from target station to drop-off
                        dfs(layout, (node){16, 31}, target_t, &tiles_dfs, false);
                    }
                }

                clock_gettime(CLOCK_REALTIME, &timestamp2);
                current = timestamp1.tv_sec * 1000000LL + timestamp1.tv_nsec / 1000;
                passed = timestamp2.tv_sec * 1000000LL + timestamp2.tv_nsec / 1000;

                passtime = passed - current;

                // Print out the result from BFS
                printf("DFS algorithm:\n");
                print_array(layout, false);
                printf("\nFinal route for DFS was %d tiles\n\n", tiles_dfs);
                printf("Total benches for DFS took %lld micros\n", passtime);
                printf("Average route for DFS took %lld micros\n\n\n", passtime/bench);

                //Clears the path from the layout array
                if (procedural) clear_path(layout, path, &tiles_dfs, targets[0]);
                clear_path(layout, path, &tiles_dfs, target_t);

                break;

            default:
                break;
        }
    }

    // Output for debug
    if (debug)
    {
        for (int j = 0; j < HEIGHT; j++)
        {
            for (int i = 0; i < WIDTH; i++)
            {
                printf("%d", vis[j][i]);
            }
            printf("\n");
        }
    }

}