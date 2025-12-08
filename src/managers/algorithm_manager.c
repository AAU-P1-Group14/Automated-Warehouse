#include "algorithm_manager.h"


void run_algorithms(int height, int width, int layout[height][width], node charging, node dropoff,
                    node target_t, int bench, bool procedural, bool debug) {

    // Creating array that contains coordinates of the robot path
    node path[height*width];

    // Clear path array
    for (int i = 0; i < height * width; i++) {
        path[i] = (node){0, 0};
    }

    node targets[bench];
    
    if (procedural) {
        for (int i = 0; i < bench; i++) {
            targets[i] = random_target(height, width, layout);
        }
    }

    // Context based print
    if (!procedural) printf("TARGET SHELF: (%d, %d)\n", target_t.y, target_t.x);
    else printf("TARGET SHELF: PROCEDURAL\n");
    printf("BENCHES: (%d)\n\n", bench);

    // Statistics for comparison
    bool found_target_worst_case = false;
    bool found_target_bfs = false;
    bool found_target_dfs = false;

    long total_tiles_worst_case = 0;
    long total_tiles_bfs = 0;
    long total_tiles_dfs = 0;

    long elapsed_worst_case = 0;
    long elapsed_bfs = 0;
    long elapsed_dfs = 0;

    long direction_switches_worst_case = 0;
    long direction_switches_dfs = 0;
    long direction_switches_bfs = 0;

    for (int i = 0; i < 3; i++) {

        // Input target in layout array
        if (!procedural) layout[target_t.y][target_t.x] = target;

        switch (i) {

            // Worst case algorithm
            case 0:
                {

                    // Worst case algorithm (random movement)
                    // Procedural
                    if (procedural) {
                        for (int i = 0; i < bench-1; i++) {
                            total_tiles_worst_case += worst_case(height, width, layout,
                                &direction_switches_worst_case, targets[i], dropoff, charging, charging, &elapsed_worst_case);

                            // Progress bar
                            progress_bar(i, bench);
                        }
                    }

                    // For the same random target
                    else {
                        for (int i = 0; i < bench-1; i++) {
                            total_tiles_worst_case += worst_case(height, width, layout,
                                &direction_switches_worst_case, target_t, dropoff, charging, charging, &elapsed_worst_case);

                            // Progress bar
                            progress_bar(i, bench);
                        }
                    }
                    // Fjern indhold på linjen
                    printf("\r");

                    // Systematicly run through the whole layout array to clear path
                    force_clear_path(width, height, layout);

                // One last run to store the path
                    if (procedural) {
                        total_tiles_worst_case += worst_case(height, width, layout, &direction_switches_worst_case,
                            targets[bench-1], dropoff, charging, charging, &elapsed_worst_case);

                        layout[targets[bench-1].y][targets[bench-1].x] = target;
                    }
                    else {
                        total_tiles_worst_case += worst_case(height, width, layout, &direction_switches_worst_case,
                            target_t, dropoff, charging, charging, &elapsed_worst_case);

                        layout[target_t.y][target_t.x] = target;
                    }

                    found_target_worst_case = total_tiles_worst_case > 0;
                    // Print out the result from worst case
                    print_stats_individual(height, width, layout, direction_switches_worst_case, total_tiles_worst_case,
                        bench, elapsed_worst_case, "Worst Case");

                    //Clears the path from the layout array
                    force_clear_path(height, width, layout);

                    break;
                }
            // BFS algorithm
            case 1:
                {
                if (procedural) {
                    for (int i = 0; i < bench-1; i++) {

                        // BFS Path finding algorithm, adding the path from charging station to target
                        bfs(height, width, layout, &direction_switches_bfs, targets[i], charging,
                            &total_tiles_bfs, path, false, &elapsed_bfs);

                        // Adding in-between direction switch
                        direction_switches_bfs++;

                        // BFS Path finding algorithm, adding the path from target station to drop-off
                        bfs(height, width, layout, &direction_switches_bfs, dropoff, targets[i],
                            &total_tiles_bfs, path, false, &elapsed_bfs);

                        // Progress bar
                        progress_bar(i, bench);
                    }

                }

                else {
                    for (int i = 0; i < bench-1; i++) {
                        // BFS Path finding algorithm, adding the path from charging station to target
                        bfs(height, width, layout, &direction_switches_bfs, target_t, charging,
                            &total_tiles_bfs, path, false, &elapsed_bfs);

                        // Adding in-between direction switch
                        direction_switches_bfs++;

                        // BFS Path finding algorithm, adding the path from target station to drop-off
                        bfs(height, width, layout, &direction_switches_bfs, dropoff, target_t,
                            &total_tiles_bfs, path, false, &elapsed_bfs);

                        // Progress bar
                        progress_bar(i, bench);
                    }
                }
                printf("\r");

                    // Run a last time, adding the path to the layout array
                if (procedural) {
                    bfs(height, width, layout, &direction_switches_bfs, targets[bench-1], charging,
                        &total_tiles_bfs, path, true, &elapsed_bfs);

                    // Adding in-between direction switch
                    direction_switches_bfs++;

                    bfs(height, width, layout, &direction_switches_bfs, dropoff, targets[bench-1],
                        &total_tiles_bfs, path, true, &elapsed_bfs);
                    layout[targets[bench-1].y][targets[bench-1].x] = target;
                }
                else {
                    bfs(height, width, layout, &direction_switches_bfs, target_t, charging,
                        &total_tiles_bfs, path, true, &elapsed_bfs);

                    // Adding in-between direction switch
                    direction_switches_bfs++;

                    bfs(height, width, layout, &direction_switches_bfs, dropoff, target_t,
                        &total_tiles_bfs, path, true, &elapsed_bfs);
                }

                found_target_bfs = total_tiles_bfs > 0;

                // Print out the result from BFS
                print_stats_individual(height, width, layout, direction_switches_bfs, total_tiles_bfs, bench,
                    elapsed_bfs, "BFS");

                //Clears the path from the layout array         
                force_clear_path(height, width, layout);

                break;
                }

            // DFS
            case 2:
                {
                if (procedural) {
                    for (int i = 0; i < bench-1; i++) {
                        // DFS Path finding algorithm, adding the path from charging station to target
                        dfs(height, width, layout, &direction_switches_dfs, path, targets[i], charging, &total_tiles_dfs, false, &elapsed_dfs);

                        // Adding in-between direction switch
                        direction_switches_dfs++;

                        // DFS Path finding algorithm, adding the path from target station to drop-off
                        dfs(height, width, layout, &direction_switches_dfs, path, dropoff, targets[i], &total_tiles_dfs, false, &elapsed_dfs);

                        progress_bar(i, bench);
                    }

                }
                
                else {
                    for (int i = 0; i < bench-1; i++) {
                        // DFS Path finding algorithm, adding the path from charging station to target
                        dfs(height, width, layout, &direction_switches_dfs, path, target_t, charging, &total_tiles_dfs, false, &elapsed_dfs);

                        // Adding in-between direction switch
                        direction_switches_dfs++;

                        // DFS Path finding algorithm, adding the path from target station to drop-off
                        dfs(height, width, layout, &direction_switches_dfs, path, dropoff, target_t, &total_tiles_dfs, false, &elapsed_dfs);

                        progress_bar(i, bench);
                    }
                }
                printf("\r");
                

                if (procedural) {
                    dfs(height, width, layout, &direction_switches_dfs, path, targets[bench-1], charging, &total_tiles_dfs, true, &elapsed_dfs);
                    
                    // Adding in-between direction switch
                    direction_switches_dfs++;
                    
                    dfs(height, width, layout, &direction_switches_dfs, path, dropoff, targets[bench-1], &total_tiles_dfs, true, &elapsed_dfs);
                    layout[targets[bench-1].y][targets[bench-1].x] = target;
                }
                else {
                    dfs(height, width, layout, &direction_switches_dfs, path, target_t, charging, &total_tiles_dfs, true, &elapsed_dfs);
                    
                    // Adding in-between direction switch
                    direction_switches_dfs++;

                    dfs(height, width, layout, &direction_switches_dfs, path, dropoff, target_t, &total_tiles_dfs, true, &elapsed_dfs);
                }

                found_target_dfs = total_tiles_dfs > 0;

                // Print out the result from BFS
                print_stats_individual(height, width, layout, direction_switches_dfs, total_tiles_dfs, bench, elapsed_dfs, "DFS");

                //Clears the path from the layout array
                force_clear_path(height, width, layout);

                break;
                }
            default:
                break;
        }
    }


    compare_results(bench, total_tiles_worst_case, total_tiles_bfs, total_tiles_dfs,
                    elapsed_worst_case, elapsed_bfs, elapsed_dfs,
                    direction_switches_worst_case, direction_switches_bfs, direction_switches_dfs,
                    found_target_worst_case, found_target_bfs, found_target_dfs);

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


void progress_bar(int counter, int done) {
    if (counter % (done < 100 ? 1 : done / 100) == 0) {
        int progress = counter * 100 / done;
        printf("\rPROGRESS: %d%%", progress);
    }
}


void print_stats_individual(int height, int width, int layout[height][width], long direction_switches,
    long long total_tiles, int bench, long long passtime, char* name) {

    printf("%s algorithm:\n", name);

    long realistic_time = calculate_realistic_time(total_tiles, direction_switches, total_tiles/bench > 0);

    print_array(height, width, layout, false);

    if (total_tiles > 0) {
        printf("\nTotal tiles traveled for %s was %lld tiles\n", name, total_tiles);
        printf("Average route for %s was %lld tiles\n\n", name, total_tiles/bench);
    }
    // Target was not found
    else printf("\n%s never reached target or drop-off\n\n", name);

    printf("Total benches for %s took %lld micros\n", name, passtime);
    printf("Average route for %s took %lld micros\n\n", name, passtime/bench);

    printf("Total direction changes: %ld\n", direction_switches);
    printf("Average direction changes: %ld\n\n", direction_switches/bench);

    printf("Total realistic time: %ld sec\n", realistic_time);
    printf("Average realistic time: %ld sec\n\n\n", realistic_time/bench);

}


void compare_results(int bench, long tiles_worst_case, long tiles_bfs, long tiles_dfs,
                     long elapsed_worst_case, long elapsed_bfs, long elapsed_dfs,
                     long direction_switches_worst_case, long direction_switches_bfs, long direction_switches_dfs,
                     bool found_worst_case, bool found_bfs, bool found_dfs) {

    printf("\n\n\n---------------------- COMPARISON TO WORST CASE (averages) ----------------------\n\n");

    long realistic_time_worst_case = calculate_realistic_time(tiles_worst_case, direction_switches_worst_case, found_worst_case);

    // BFS -------------------
    
    // Comparing tiles with worst case
    long tiles_compare_bfs = (tiles_bfs - tiles_worst_case) / bench;

    // Comparing elapsed time with worst case
    long elapsed_compare_bfs = (elapsed_bfs - elapsed_worst_case) / bench;

    long direction_switches_compare_bfs = (direction_switches_bfs - direction_switches_worst_case) / bench;

    // Comparing realistic time with worst case
    long realistic_time_bfs = calculate_realistic_time(tiles_bfs, direction_switches_bfs, found_bfs);
    long realistic_time_compare_bfs = (realistic_time_bfs - realistic_time_worst_case) / bench;

    print_comparison("Breadth First search (BFS)", found_bfs, bench,
        tiles_bfs, tiles_compare_bfs,
        elapsed_bfs, elapsed_compare_bfs,
        direction_switches_bfs, direction_switches_compare_bfs,
        realistic_time_bfs, realistic_time_compare_bfs);



    // DFS -------------------

    // Comparing tiles with worst case
    long tiles_compare_dfs = (tiles_dfs - tiles_worst_case) / bench;

    // Comparing elapsed time with worst case
    long elapsed_compare_dfs = (elapsed_dfs - elapsed_worst_case) / bench;

    long direction_switches_compare_dfs = (direction_switches_dfs - direction_switches_worst_case) / bench;

    // Comparing realistic time with worst case
    long realistic_time_dfs = calculate_realistic_time(tiles_dfs, direction_switches_dfs, found_dfs);
    long realistic_time_compare_dfs = (realistic_time_dfs - realistic_time_worst_case) / bench;  

    print_comparison("Depth First Search (DFS)", found_dfs, bench,
        tiles_dfs, tiles_compare_dfs,
        elapsed_dfs, elapsed_compare_dfs,
        direction_switches_dfs, direction_switches_compare_dfs,
        realistic_time_dfs, realistic_time_compare_dfs);

    // END
    printf("---------------------------------------------------------------------------------\n\n");
}


long calculate_realistic_time(long tiles, long direction_switches, bool found_target) {
    long result_seconds = 0;
    if (!found_target) result_seconds = tiles * TILES_PER_SECOND + direction_switches * 2;
    else result_seconds = tiles * TILES_PER_SECOND + direction_switches * 2 + 10;
    return result_seconds;
}


void print_comparison(char algo_name[40], bool found_target, int bench,
    long tiles, long tiles_compare,
    long elapsed_time, long compare_elapsed_time,
    long direction_changes, long direction_changes_compare,
    long realistic_time, long realistic_time_compare) {

    printf(">>> %s <<<\n", algo_name);

    if (found_target) printf("Target found: " GREEN "Yes" COLOR_RESET "\n");
    else printf("Target found: " RED "No" COLOR_RESET "\n");

    if (direction_changes_compare < 0)
    {
        printf("Direction switches: %ld (" GREEN "%+ld" COLOR_RESET ")\n",
               direction_changes / bench, direction_changes_compare);
    }
    else
    {
        printf("Direction switches: %ld (" RED "%+ld" COLOR_RESET ")\n",
               direction_changes / bench, direction_changes_compare);
    }


    if (tiles_compare < 0) printf("Tiles: %ld (" GREEN "%+ld" COLOR_RESET ")\n", tiles / bench, tiles_compare);
    else printf("Tiles: %ld (" RED "%+ld" COLOR_RESET ")\n", tiles / bench, tiles_compare);

    if (compare_elapsed_time < 0)
    {
        printf("Algorithm time: %ld micro sec (" GREEN "%+ld " COLOR_RESET "micro sec)\n",
               elapsed_time / bench, compare_elapsed_time);
    }
    else
    {
        printf("Algorithm time: %ld micro sec (" RED "%+ld micro sec " COLOR_RESET ")\n",
               elapsed_time / bench, compare_elapsed_time);
    }

    if (realistic_time_compare < 0)
    {
        printf("Realistic time: %ld sec (" GREEN "%+ld " COLOR_RESET "sec)\n\n",
               realistic_time / bench, realistic_time_compare);
    }
    else
    {
        printf("Realistic time: %ld sec (" RED "%+ld " COLOR_RESET "sec)\n\n",
               realistic_time / bench, realistic_time_compare / bench);
    }

}