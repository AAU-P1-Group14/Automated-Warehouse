#include <time.h>
#include <stdio.h>

#include "input_manager.h"
#include "../utility/types.h"
#include "../algorithms/bfs.h"
#include "../algorithms/dfs.h"
#include "../algorithms/worst_case.h"

void run_algorithms(int height, int width, int layout[height][width], node charging, node dropoff, node target_t, int bench, bool procedural, bool debug);