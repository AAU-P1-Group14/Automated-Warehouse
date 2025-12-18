# Automated-Warehouse
This tool is designed to simulate different algorithms and benchmark them on either a predefined or user-created dynamic layout.

## User Options

The following shows the program's user interface, which lists 7 options:

#### (1) - Start Simulation
Runs the algorithms after configuring the warehouse environment.

#### (2) - Custom Target
Allows the user to choose a custom pickup shelf.

#### (3) - Random Target
Selects a random target.

#### (4) - Predefined Layout
Sets the layout to the default layout. Useful if you previously chose a custom layout but want to revert.

#### (5) - Dynamic Layout
Allows the user to create a custom layout (within certain limits) with 5 different customization parameters.

#### (6) - Select Benches
Lets the user choose how many benchmarks (benches) the algorithms should run before returning results.

#### (0) - Exit
Exits the program.

<img width="277" height="354" alt="Screenshot 2025-12-18 at 10 32 15" src="https://github.com/user-attachments/assets/532c6f77-770d-4a4a-91ba-0b4a758ef080" />

When the program runs, the user can customize all of the above parameters to their preference. After configuration, the simulation can be started by selecting option 1.

## Algorithm Output

This shows an example of what the output from the BFS algorithm could look like:

![Algorithm Output Example](../../../../../var/folders/l2/lkryvpwj233dnzz34bn9kmrm0000gn/T/TemporaryItems/NSIRD_screencaptureui_cvPjeT/Screenshot%202025-12-18%20at%2011.03.12.png)

#### Total tiles traveled for BFS was
The total amount of tiles traveled.

#### Average route for BFS was
The average length of the path it found.

#### Total benches for BFS took
The total combined time.

#### Average route for BFS took
The average time per bench.

#### Total direction changes
How many times the robot changed directions.

#### Average direction changes
The average number of direction changes per route.

#### Total realistic time
Estimated total time for the route in a real-world scenario.

#### Average realistic time
Estimated average time per bench in a real-world scenario.
