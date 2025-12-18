# Automated-Warehouse
This tool is designed to simulate different algorithms and benchmark them on either a predefined or user-created dynamic layout.

## User Options

### The following shows the program's user interface, which lists 7 options:

#### (1) - Start Simulation
- Runs the algorithms after configuring the warehouse environment.

#### (2) - Custom Target
- Allows the user to choose a custom pickup shelf.

#### (3) - Random Target
- Selects a random target.

#### (4) - Predefined Layout
-  Sets the layout to the default layout. Useful if you previously chose a custom layout but want to revert.

#### (5) - Dynamic Layout
-  Allows the user to create a custom layout (within certain limits) with 5 different customization parameters.

#### (6) - Select Benches
- Lets the user choose how many benchmarks (benches) the algorithms should run before returning results.

#### (0) - Exit
- Exits the program.

<img width="277" height="354" alt="Screenshot 2025-12-18 at 10 32 15" src="https://github.com/user-attachments/assets/532c6f77-770d-4a4a-91ba-0b4a758ef080" />

When the program runs, the user can customize all of the above parameters to their preference. Every time the user has customised a setting, they will return to this menu. After configuration, the simulation can be started by selecting option 1.

## Output

### Algorithms
This shows an example of what the output from the BFS algorithm could look like. The output for BFS, DFS and worst-case follows the same structure and includes the same results.


<img width="575" height="708" alt="Screenshot 2025-12-18 at 11 38 58" src="https://github.com/user-attachments/assets/22a364cd-9882-430c-93b9-77dda48358a8" />

#### Total tiles traveled for BFS was:
- The total amount of tiles traveled.

#### Average route for BFS was:
- The average length of the path it found.

#### Total benches for BFS took:
- The total combined time in micro seconds that it took for the algorithm to finish.

#### Average route for BFS took:
- The average time per bench in micro seconds that it took for the algorithm to finish.

#### Total direction changes:
- How many times the robot changed directions.

#### Average direction changes:
- The average number of direction changes per route.

#### Total realistic time:
- Estimated total time for the robot in a real-world scenario.

#### Average realistic time:
- Estimated average time for the robot in a real-world scenario per bench.

### Comparison
- This is a comparison in the end that compares BFS and DFS to worst case.

<img width="658" height="419" alt="Screenshot 2025-12-18 at 11 39 12" src="https://github.com/user-attachments/assets/ca0ea094-af42-4f1a-8a43-b82a11e68ad6" />


#### Target Found:
- If the algorithm found the target.

#### Direction switches:
- The average amount of direction switches.

#### Tiles:
- The average length of the path in tiles.

#### Algorithm Time:
- The time it took for the algorithm to funish in micro seconds

#### Realistic Time:
- An estimated realistic time it would take for the robot to complete the operation
