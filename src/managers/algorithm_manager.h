#include <time.h>
#include <stdio.h>

#include "input_manager.h"
#include "../utility/types.h"
#include "../algorithms/bfs.h"
#include "../algorithms/dfs.h"
#include "../algorithms/worst_case.h"

#define TILES_PER_SECOND (1/1.4)

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define BLUE    "\x1b[34m"
#define COLOR_RESET   "\x1b[0m"

void run_algorithms(int height, int width, int layout[height][width], node charging, node dropoff, node target_t, int bench, bool procedural, bool debug);
void progress_bar(int counter, int done);
void print_stats_individual(int height, int width, int layout[height][width], long long direction_switches,
    long long total_tiles, int bench, long long passtime, char* name, int failed_runs);
void compare_results(int bench, int failed_runs, long long tiles_worst_case, long long tiles_bfs, long long tiles_dfs,
                     long long elapsed_worst_case, long long elapsed_bfs, long long elapsed_dfs,
                     long long direction_switches_worst_case, long long direction_switches_bfs, long long direction_switches_dfs,
                     bool found_worst_case, bool found_bfs, bool found_dfs);
long long calculate_realistic_time(long long tiles, long long direction_switches, bool found_target);
void print_comparison(char algo_name[40], bool found_target, int bench,
    long long tiles, long long tiles_compare,
    long long elapsed_time, long long compare_elapsed_time,
    long long direction_changes, long long direction_changes_compare,
    long long realistic_time, long long realistic_time_compare);