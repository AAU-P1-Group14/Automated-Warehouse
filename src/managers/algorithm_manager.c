#include "algorithm_manager.h"

void print_stats(int *height, int *width, int layout[*height][*width], long long total_tiles, int bench, long long passtime, char* name) {
    printf("%s algorithm:\n", name);
    print_array(*height, *width, layout, false);
    if (total_tiles/bench > 0) {
        printf("\nTotal tiles traveled for %s was %lld tiles\n", name, total_tiles);
        printf("Average route for %s was %lld tiles\n\n", name, total_tiles/bench);
    } else printf("\n%s never reached target or drop-off\n\n", name);
    printf("Total benches for %s took %lld micros\n", name, passtime);
    printf("Average route for %s took %lld micros\n\n\n", name, passtime/bench);
}

void run_algorithms(int height, int width, int layout[height][width], node charging, node dropoff, node target_t, int bench, bool procedural, bool debug) {
    // Creating array that contains coordinates of the robot path
    node path[height*width];

    for (int i = 0; i < height * width; i++) {
        path[i] = (node){0, 0};
    }

    //node targets[bench];
    node *targets = malloc(sizeof(node) * bench);

    if (procedural) {
        for (int i = 0; i < bench; i++) {
            targets[i] = random_target(height, width, layout);
        }
    }

    if (!procedural) printf("TARGET SHELF: (%d, %d)\n", target_t.y, target_t.x);
    else printf("TARGET SHELF: PROCEDURAL\n");
    printf("BENCHES: (%d)\n\n", bench);

    for (int i = 0; i < 3; i++) {

        // Input target in layout array
        if (!procedural) layout[target_t.y][target_t.x] = target;

        struct timespec timestamp1;
        struct timespec timestamp2;

        int tiles_bfs = 0;
        int tiles_dfs = 0;
        long long total_tiles = 0;

        switch (i) {
            case 0:
                clock_gettime(CLOCK_REALTIME, &timestamp1);

                // Worst case algorithm (random movement)
                if (procedural) {
                    for (int i = 0; i < bench-1; i++) {
                        total_tiles += worst_case(height, width, layout, targets[i], dropoff, charging, charging);

                        if (i % (bench < 100 ? 1 : bench / 100) == 0) {
                            int progress = i * 100 / bench;
                            printf("\rPROGRESS: %d%%", progress);
                        }
                    }
                    printf("\r");
                }

                else {
                    for (int i = 0; i < bench-1; i++) {
                        total_tiles += worst_case(height, width, layout, target_t, dropoff, charging, charging);

                        if (i % (bench < 100 ? 1 : bench / 100) == 0) {
                            int progress = i * 100 / bench;
                            printf("\rPROGRESS: %d%%", progress);
                        }
                    }
                }

                // One last run to store the path
                force_clear_path(width, height, layout);
                if (procedural) {
                    total_tiles += worst_case(height, width, layout, targets[bench-1], dropoff, charging, charging);
                    layout[targets[bench-1].y][targets[bench-1].x] = target;
                }
                else total_tiles += worst_case(height, width, layout, target_t, dropoff, charging, charging);

                // Calculate the time it took
                clock_gettime(CLOCK_REALTIME, &timestamp2);
                long long current = timestamp1.tv_sec * 1000000LL + timestamp1.tv_nsec / 1000;
                long long passed = timestamp2.tv_sec * 1000000LL + timestamp2.tv_nsec / 1000;

                long long passtime = passed - current;

                // Print out the result from worst case
                print_stats(&height, &width, layout, total_tiles, bench, passtime, "Worst Case");

                //Clears the path from the layout array
                force_clear_path(height, width, layout);

                break;
            case 1:
                {
                if (procedural) {
                    clock_gettime(CLOCK_REALTIME, &timestamp1);

                    for (int i = 0; i < bench-1; i++) {
                        // BFS Path finding algorithm, adding the path from charging station to target
                        bfs(height, width, layout, targets[i], charging, &tiles_bfs, &total_tiles, path, false);

                        // BFS Path finding algorithm, adding the path from target station to drop-off
                        bfs(height, width, layout, dropoff, targets[i], &tiles_bfs, &total_tiles, path, false);

                        if (i % (bench < 100 ? 1 : bench / 100) == 0) {
                            int progress = i * 100 / bench;
                            printf("\rPROGRESS: %d%%", progress);
                        }
                    }
                    printf("\r");

                } else {
                    clock_gettime(CLOCK_REALTIME, &timestamp1);

                    for (int i = 0; i < bench-1; i++) {
                        // BFS Path finding algorithm, adding the path from charging station to target
                        bfs(height, width, layout, target_t, charging, &tiles_bfs, &total_tiles, path, false);

                        // BFS Path finding algorithm, adding the path from target station to drop-off
                        bfs(height, width, layout, dropoff, target_t, &tiles_bfs, &total_tiles, path, false);
                    }
                }

                if (procedural) {
                    bfs(height, width, layout, targets[bench-1], charging, &tiles_bfs, &total_tiles, path, true);
                    bfs(height, width, layout, dropoff, targets[bench-1], &tiles_bfs, &total_tiles, path, true);
                    layout[targets[bench-1].y][targets[bench-1].x] = target;
                }
                else {
                    bfs(height, width, layout, target_t, charging, &tiles_bfs, &total_tiles, path, true);
                    bfs(height, width, layout, dropoff, target_t, &tiles_bfs, &total_tiles, path, true);
                }

                clock_gettime(CLOCK_REALTIME, &timestamp2);
                current = timestamp1.tv_sec * 1000000LL + timestamp1.tv_nsec / 1000;
                passed = timestamp2.tv_sec * 1000000LL + timestamp2.tv_nsec / 1000;

                passtime = passed - current;

                // Print out the result from BFS
                print_stats(&height, &width, layout, total_tiles, bench, passtime, "BFS");

                //Clears the path from the layout array
                if (procedural) clear_path(height, width, layout, path, &tiles_bfs, targets[0]);
                clear_path(height, width, layout, path, &tiles_bfs, target_t);

                break;
                }
            case 2:
                {
                if (procedural) {
                    clock_gettime(CLOCK_REALTIME, &timestamp1);

                    for (int i = 0; i < bench-1; i++) {
                        // DFS Path finding algorithm, adding the path from charging station to target
                        dfs(height, width, layout, path, targets[i], charging, &tiles_dfs, &total_tiles, false);

                        printf("TARGET: (%d, %d)\n", targets[i].y, targets[i].x);
                        printf("CHARGING: (%d, %d)\n", charging.y, charging.x);

                        // DFS Path finding algorithm, adding the path from target station to drop-off
                        dfs(height, width, layout, path, dropoff, targets[i], &tiles_dfs, &total_tiles, false);

                        if (i % (bench < 100 ? 1 : bench / 100) == 0) {
                            int progress = i * 100 / bench;
                            printf("\rPROGRESS: %d%%", progress);
                        }
                    }
                    printf("\r");

                } else {
                    clock_gettime(CLOCK_REALTIME, &timestamp1);

                    for (int i = 0; i < bench-1; i++) {
                        // DFS Path finding algorithm, adding the path from charging station to target
                        dfs(height, width, layout, path, target_t, charging, &tiles_dfs, &total_tiles, false);
                        printf("TARGET: (%d, %d)\n", target_t.y, target_t.x);
                        printf("CHARGING: (%d, %d)\n", charging.y, charging.x);
                        // DFS Path finding algorithm, adding the path from target station to drop-off
                        dfs(height, width, layout, path, dropoff, target_t, &tiles_dfs, &total_tiles, false);
                    }
                }

                if (procedural) {
                    dfs(height, width, layout, path, targets[bench-1], charging, &tiles_dfs, &total_tiles, true);
                    dfs(height, width, layout, path, dropoff, targets[bench-1], &tiles_dfs, &total_tiles, true);
                    layout[targets[bench-1].y][targets[bench-1].x] = target;
                }
                else {
                    dfs(height, width, layout, path, target_t, charging, &tiles_dfs, &total_tiles, true);
                    dfs(height, width, layout, path, dropoff, target_t, &tiles_dfs, &total_tiles, true);
                }

                clock_gettime(CLOCK_REALTIME, &timestamp2);
                current = timestamp1.tv_sec * 1000000LL + timestamp1.tv_nsec / 1000;
                passed = timestamp2.tv_sec * 1000000LL + timestamp2.tv_nsec / 1000;

                passtime = passed - current;

                // Print out the result from BFS
                print_stats(&height, &width, layout, total_tiles, bench, passtime, "DFS");

                //Clears the path from the layout array
                if (procedural) clear_path(height, width, layout, path, &tiles_dfs, targets[0]);
                clear_path(height, width, layout, path, &tiles_dfs, target_t);

                break;
                }
            default:
                break;
        }
    }

    free(targets);

    // Output for debug
    if (debug)
    {
        for (int j = 0; j < height; j++)
        {
            for (int i = 0; i < width; i++)
            {
                printf("%d", vis[j][i]);
            }
            printf("\n");
        }
    }
}