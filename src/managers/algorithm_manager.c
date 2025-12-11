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

    long long total_tiles_worst_case = 0;
    long long total_tiles_bfs = 0;
    long long total_tiles_dfs = 0;

    long long elapsed_worst_case = 0;
    long long elapsed_bfs = 0;
    long long elapsed_dfs = 0;

    long long direction_switches_worst_case = 0;
    long long direction_switches_dfs = 0;
    long long direction_switches_bfs = 0;

    for (int i = 0; i < 3; i++) {

        int failed_runs = 0;

        // Input target in layout array
        if (!procedural) layout[target_t.y][target_t.x] = target;

        switch (i) {

            // Worst case algorithm
            case 0:
                {

                    // Worst case algorithm (random movement)
                    // Procedural
                    if (procedural) {

                        // Result for checking if the path-finding run is successful
                        int result = 0;

                        for (int i = 0; i < bench-1; i++) {
                             result = worst_case(height, width, layout,
                                &direction_switches_worst_case, targets[i], dropoff, charging, charging, &elapsed_worst_case);

                            if (result == 0)
                                failed_runs++;
                            else
                                total_tiles_worst_case += result;

                            // Progress bar
                            progress_bar(i, bench);
                        }
                    }

                    // For the same random target
                    else {

                        // Result for checking if the path-finding run is successful
                        int result = 0;

                        for (int i = 0; i < bench-1; i++) {
                            result = worst_case(height, width, layout,
                                &direction_switches_worst_case, target_t, dropoff, charging, charging, &elapsed_worst_case);

                            if (result == 0)
                                failed_runs++;
                            else
                                total_tiles_worst_case += result;

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
                        int result = worst_case(height, width, layout, &direction_switches_worst_case,
                            targets[bench-1], dropoff, charging, charging, &elapsed_worst_case);

                        if (result == 0)
                            failed_runs++;
                        else
                            total_tiles_worst_case += result;

                        layout[targets[bench-1].y][targets[bench-1].x] = target;
                    }
                    else {
                        int result = worst_case(height, width, layout, &direction_switches_worst_case,
                            target_t, dropoff, charging, charging, &elapsed_worst_case);

                        if (result == 0)
                            failed_runs++;
                        else
                            total_tiles_worst_case += result;

                        layout[target_t.y][target_t.x] = target;
                    }

                    found_target_worst_case = total_tiles_worst_case > 0;
                    // Print out the result from worst case
                    print_stats_individual(height, width, layout, direction_switches_worst_case, total_tiles_worst_case,
                        bench, elapsed_worst_case, "Worst Case", failed_runs);

                    //Clears the path from the layout array
                    force_clear_path(height, width, layout);

                    break;
                }
            // BFS algorithm
            case 1:
                {
                if (procedural) {

                    // Result for checking if the path-finding run is successful
                    int result = 0;

                    for (int i = 0; i < bench-1; i++) {

                        // BFS Path finding algorithm, adding the path from charging station to target
                        bfs(height, width, layout, &direction_switches_bfs, targets[i], charging,
                            &total_tiles_bfs, path, false, &elapsed_bfs);

                        // Adding in-between direction switch
                        direction_switches_bfs++;

                        // BFS Path finding algorithm, adding the path from target station to drop-off
                        result = bfs(height, width, layout, &direction_switches_bfs, dropoff, targets[i],
                            &total_tiles_bfs, path, false, &elapsed_bfs);

                        if (result == 0)
                            failed_runs++;

                        // Progress bar
                        progress_bar(i, bench);
                    }

                }

                else {

                    // Result for checking if the path-finding run is successful
                    int result = 0;

                    for (int i = 0; i < bench-1; i++) {
                        // BFS Path finding algorithm, adding the path from charging station to target
                        bfs(height, width, layout, &direction_switches_bfs, target_t, charging,
                            &total_tiles_bfs, path, false, &elapsed_bfs);

                        // Adding in-between direction switch
                        direction_switches_bfs++;

                        // BFS Path finding algorithm, adding the path from target station to drop-off
                        result = bfs(height, width, layout, &direction_switches_bfs, dropoff, target_t,
                            &total_tiles_bfs, path, false, &elapsed_bfs);

                        if (result == 0)
                            failed_runs++;

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

                    int result = bfs(height, width, layout, &direction_switches_bfs, dropoff, targets[bench-1],
                        &total_tiles_bfs, path, true, &elapsed_bfs);

                    if (result == 0)
                        failed_runs++;

                    layout[targets[bench-1].y][targets[bench-1].x] = target;
                }
                else {
                    bfs(height, width, layout, &direction_switches_bfs, target_t, charging,
                        &total_tiles_bfs, path, true, &elapsed_bfs);

                    // Adding in-between direction switch
                    direction_switches_bfs++;

                    int result = bfs(height, width, layout, &direction_switches_bfs, dropoff, target_t,
                        &total_tiles_bfs, path, true, &elapsed_bfs);

                    if (result == 0)
                        failed_runs++;
                }

                found_target_bfs = total_tiles_bfs > 0;

                // Print out the result from BFS
                print_stats_individual(height, width, layout, direction_switches_bfs, total_tiles_bfs, bench,
                    elapsed_bfs, "BFS", failed_runs);

                //Clears the path from the layout array         
                force_clear_path(height, width, layout);

                break;
                }

            // DFS
            case 2:
                {
                if (procedural) {

                    // Result for checking if the path-finding run is successful
                    int result = 0;

                    for (int i = 0; i < bench-1; i++) {
                        // DFS Path finding algorithm, adding the path from charging station to target
                        dfs(height, width, layout, &direction_switches_dfs, path, targets[i], charging, &total_tiles_dfs, false, &elapsed_dfs);

                        // Adding in-between direction switch
                        direction_switches_dfs++;

                        // DFS Path finding algorithm, adding the path from target station to drop-off
                        result = dfs(height, width, layout, &direction_switches_dfs, path, dropoff, targets[i], &total_tiles_dfs, false, &elapsed_dfs);

                        if (result == 0)
                            failed_runs++;

                        progress_bar(i, bench);
                    }

                }
                
                else {

                    // Result for checking if the path-finding run is successful
                    int result = 0;

                    for (int i = 0; i < bench-1; i++) {
                        // DFS Path finding algorithm, adding the path from charging station to target
                        dfs(height, width, layout, &direction_switches_dfs, path, target_t, charging, &total_tiles_dfs, false, &elapsed_dfs);

                        // Adding in-between direction switch
                        direction_switches_dfs++;

                        // DFS Path finding algorithm, adding the path from target station to drop-off
                        result = dfs(height, width, layout, &direction_switches_dfs, path, dropoff, target_t, &total_tiles_dfs, false, &elapsed_dfs);

                        if (result == 0)
                            failed_runs++;

                        progress_bar(i, bench);
                    }
                }
                printf("\r");
                

                if (procedural) {
                    dfs(height, width, layout, &direction_switches_dfs, path, targets[bench-1], charging, &total_tiles_dfs, true, &elapsed_dfs);
                    
                    // Adding in-between direction switch
                    direction_switches_dfs++;
                    
                    int result = dfs(height, width, layout, &direction_switches_dfs, path, dropoff, targets[bench-1], &total_tiles_dfs, true, &elapsed_dfs);
                    layout[targets[bench-1].y][targets[bench-1].x] = target;

                    if (result == 0)
                        failed_runs++;

                }
                else {
                    dfs(height, width, layout, &direction_switches_dfs, path, target_t, charging, &total_tiles_dfs, true, &elapsed_dfs);
                    
                    // Adding in-between direction switch
                    direction_switches_dfs++;

                    int result = dfs(height, width, layout, &direction_switches_dfs, path, dropoff, target_t, &total_tiles_dfs, true, &elapsed_dfs);

                    if (result == 0)
                        failed_runs++;
                }

                found_target_dfs = total_tiles_dfs > 0;

                // Print out the result from BFS
                print_stats_individual(height, width, layout, direction_switches_dfs, total_tiles_dfs, bench, elapsed_dfs, "DFS", failed_runs);

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
        fflush(stdout);
    }
}


void print_stats_individual(int height, int width, int layout[height][width], long long direction_switches,
    long long total_tiles, int bench, long long passtime, char* name, int failed_runs) {

    printf("%s algorithm:\n", name);

    long long realistic_time = calculate_realistic_time(total_tiles, direction_switches, total_tiles/bench > 0);

    print_array(height, width, layout, false);

    if (failed_runs > 0) {
        printf(RED "\nFailed path-finding runs: %d of %d" COLOR_RESET "\n\n",
               failed_runs, bench);
    }

    if (total_tiles > 0) {
        printf("\nTotal tiles traveled for %s was %lld tiles\n", name, total_tiles);
        printf("Average route for %s was %lld tiles\n\n", name, total_tiles/bench);
    }

    printf("Total benches for %s took %lld microseconds\n", name, passtime);
    printf("Average route for %s took %lld microseconds\n\n", name, passtime/bench);

    printf("Total direction changes: %lld\n", direction_switches);
    printf("Average direction changes: %lld\n\n", direction_switches/bench);

    printf("Total realistic time: %lld seconds\n", realistic_time);
    printf("Average realistic time: %lld seconds\n\n\n", realistic_time/bench);

}


void compare_results(int bench, long long tiles_worst_case, long long tiles_bfs, long long tiles_dfs,
                     long long elapsed_worst_case, long long elapsed_bfs, long long elapsed_dfs,
                     long long direction_switches_worst_case, long long direction_switches_bfs, long long direction_switches_dfs,
                     bool found_worst_case, bool found_bfs, bool found_dfs) {

    printf("\n\n\n---------------------- COMPARISON TO WORST CASE (averages) ----------------------\n\n");

    long long realistic_time_worst_case = calculate_realistic_time(tiles_worst_case, direction_switches_worst_case, found_worst_case);

    // BFS -------------------
    
    // Comparing tiles with worst case
    long long tiles_compare_bfs = (tiles_bfs - tiles_worst_case) / bench;

    // Comparing elapsed time with worst case
    long long elapsed_compare_bfs = (elapsed_bfs - elapsed_worst_case) / bench;

    long long direction_switches_compare_bfs = (direction_switches_bfs - direction_switches_worst_case) / bench;

    // Comparing realistic time with worst case
    long long realistic_time_bfs = calculate_realistic_time(tiles_bfs, direction_switches_bfs, found_bfs);
    long long realistic_time_compare_bfs = (realistic_time_bfs - realistic_time_worst_case) / bench;

    print_comparison("Breadth First search (BFS)", found_bfs, bench,
        tiles_bfs, tiles_compare_bfs,
        elapsed_bfs, elapsed_compare_bfs,
        direction_switches_bfs, direction_switches_compare_bfs,
        realistic_time_bfs, realistic_time_compare_bfs);



    // DFS -------------------

    // Comparing tiles with worst case
    long long tiles_compare_dfs = (tiles_dfs - tiles_worst_case) / bench;

    // Comparing elapsed time with worst case
    long long elapsed_compare_dfs = (elapsed_dfs - elapsed_worst_case) / bench;

    long long direction_switches_compare_dfs = (direction_switches_dfs - direction_switches_worst_case) / bench;

    // Comparing realistic time with worst case
    long long realistic_time_dfs = calculate_realistic_time(tiles_dfs, direction_switches_dfs, found_dfs);
    long long realistic_time_compare_dfs = (realistic_time_dfs - realistic_time_worst_case) / bench;

    print_comparison("Depth First Search (DFS)", found_dfs, bench,
        tiles_dfs, tiles_compare_dfs,
        elapsed_dfs, elapsed_compare_dfs,
        direction_switches_dfs, direction_switches_compare_dfs,
        realistic_time_dfs, realistic_time_compare_dfs);

    // END
    printf("---------------------------------------------------------------------------------\n\n");
}


long long calculate_realistic_time(long long tiles, long long direction_switches, bool found_target) {
    double result_seconds = 0;
    if (!found_target) result_seconds = (double)tiles * TILES_PER_SECOND + (double)direction_switches * 2;
    else result_seconds = (double)tiles * TILES_PER_SECOND + (double)direction_switches * 2 + 10;
    return (long long)result_seconds;
}


void print_comparison(char algo_name[40], bool found_target, int bench,
    long long tiles, long long tiles_compare,
    long long elapsed_time, long long compare_elapsed_time,
    long long direction_changes, long long direction_changes_compare,
    long long realistic_time, long long realistic_time_compare) {

    printf(">>> %s <<<\n", algo_name);

    if (found_target) printf("Target found: " GREEN "Yes" COLOR_RESET "\n");
    else printf("Target found: " RED "No" COLOR_RESET "\n");

    if (direction_changes_compare < 0)
    {
        printf("Direction switches: %lld (" GREEN "%+lld" COLOR_RESET ")\n",
               direction_changes / bench, direction_changes_compare);
    }
    else
    {
        printf("Direction switches: %lld (" RED "%+lld" COLOR_RESET ")\n",
               direction_changes / bench, direction_changes_compare);
    }


    if (tiles_compare < 0) printf("Tiles: %lld (" GREEN "%+lld" COLOR_RESET ")\n", tiles / bench, tiles_compare);
    else printf("Tiles: %lld (" RED "%+lld" COLOR_RESET ")\n", tiles / bench, tiles_compare);

    if (compare_elapsed_time < 0)
    {
        printf("Algorithm time: %lld micro seconds (" GREEN "%+lld " COLOR_RESET "micro seconds)\n",
               elapsed_time / bench, compare_elapsed_time);
    }
    else
    {
        printf("Algorithm time: %lld micro seconds (" RED "%+lld micro seconds " COLOR_RESET ")\n",
               elapsed_time / bench, compare_elapsed_time);
    }

    if (realistic_time_compare < 0)
    {
        printf("Realistic time: %lld seconds (" GREEN "%+lld " COLOR_RESET "seconds)\n\n",
               realistic_time / bench, realistic_time_compare);
    }
    else
    {
        printf("Realistic time: %lld seconds (" RED "%+lld " COLOR_RESET "seconds)\n\n",
               realistic_time / bench, realistic_time_compare / bench);
    }

}