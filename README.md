# Gearball Puzzle Solver
This project implements a solver for the Gearball puzzle, which is a spherical, 3D puzzle that is similar to a Rubik's cube but with more complexity.

The solver is implemented using the A* search algorithm, which can find the shortest path to the solved state of the puzzle. The user can interact with the solver through a command-line interface that allows them to perform manual rotations on the puzzle, randomize it, solve it, check if it is solved, print its current state, restart the program, or quit.

## Prerequisites
* C++ compiler
* CMake build system
* Git (optional, for cloning the repository)

## Installation
To install the program, clone the repository, navigate to the project root, and run the following commands:

```bash
mkdir build
cd build
cmake ..
make
```

This will build the program in the build directory. To run it, execute the following command in the build directory:

```bash
./gearball_puzzle
```

## Usage
The program will display a welcome message and the current state of the gearball in its solved state.

The user can then choose from the following menu options:

1. Randomize the gearball
2. Solve the gearball
3. Perform manual rotations on the ball
4. Check if the gearball is solved
5. Print gearball's current state
6. Restart program
7. Quit

If the user chooses to perform manual rotations on the gearball, they will be presented with a sub-menu that allows them to choose from different rotation options.

If the user chooses to randomize the gearball, they will be prompted to enter the number of random rotations to perform on the puzzle.

If the user chooses to solve the gearball, the program will solve the puzzle using the A* search algorithm and display the sequence of moves required to reach the solved state.

If the user chooses to check if the gearball is solved, the program will check if the current state of the puzzle is the solved state.

If the user chooses to print the current state of the gearball, the program will print the current state of the puzzle.

If the user chooses to restart the program, the program will restart and display the welcome message and the current state of the gearball in its solved state.

If the user chooses to quit, the program will exit.

## Acknowledgements
The Gearball puzzle was created by Oskar van Deventer.
