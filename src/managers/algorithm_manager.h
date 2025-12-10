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
void print_stats_individual(int height, int width, int layout[height][width], long direction_switches, long long total_tiles, int bench, long long passtime, char* name);
void compare_results(int bench, long tiles_worst_case, long tiles_bfs, long tiles_dfs,
                     long elapsed_worst_case, long elapsed_bfs, long elapsed_dfs,
                     long direction_switches_worst_case, long direction_switches_bfs, long direction_switches_dfs,
                     bool found_worst_case, bool found_bfs, bool found_dfs);
long calculate_realistic_time(long tiles, long direction_switches, bool found_target);
void print_comparison(char algo_name[40], bool found_target, int bench,
    long tiles, long tiles_compare,
    long elapsed_time, long compare_elapsed_time,
    long direction_changes, long direction_changes_compare,
    long realistic_time, long realistic_time_compare);

void newProgressBar(int count, int benches);
