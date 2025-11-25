#include <time.h>
#include <stdio.h>

#include "input_manager.h"
#include "../utility/types.h"
#include "../algorithms/bfs.h"
#include "../algorithms/dfs.h"

void run_algorithms(int layout[HEIGHT][WIDTH], node target_t, int bench, bool procedural, bool debug);