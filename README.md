# Genetic Algorithm for N-Queens Problem
## Project Overview
This project implements a genetic algorithm to solve the N-Queens problem - a classic chess puzzle that involves placing N queens on an N×N chessboard so that no queen can attack any other queen. A queen can attack horizontally, vertically, or diagonally.

## Problem Description
The N-Queens problem is a well-known combinatorial problem in computer science. The goal is to place N queens on an N×N chessboard such that:

No two queens share the same row
No two queens share the same column
No two queens share the same diagonal
In our implementation, the state size (board size) is configurable, with a default of 8×8.

## Implementation Details
### Representation
Each individual solution is represented as a string of integers
Each position (index) represents a row on the board
The value at each position represents the column where a queen is placed
For example, "02461357" represents an 8-Queens configuration
### Algorithm Components
Population Generation: Creates a random initial population of candidate solutions
Fitness Function: Calculates how many queen pairs don't threaten each other
Selection: Tournament selection to choose parents for breeding
Crossover: Single-point crossover between parent solutions
Mutation: Random changes to some positions based on a mutation rate
Replacement: New population replaces the old one each generation
## How to Build and Run
### Prerequisites
- GCC compiler
- Make utility
### Compilation
```bash
make
```
### Running the Program
```bash
make run
```
### Clean Build Files
```bash
make clean
```
## Configuration Parameters
The algorithm can be tuned by modifying these parameters in lib.h:

POPULATION_SIZE: Number of individuals in the population (default: 1000)
STATE: Size of the chessboard and number of queens (default: 8)
MAX_GENERATIONS: Maximum number of evolution iterations (default: 7000)
Output Interpretation
When the program runs, it outputs:

Attended value: The maximum possible fitness value (perfect solution)
Returned value: The fitness of the best solution found
Details about the best solution including:
Solution representation
Probability (fitness relative to population)
Generation when found
Fitness value
## Algorithm Variants
The code includes:

genetic_algorithm: The primary implementation using tournament selection
roulette_wheel_selection: Alternative selection method (commented out in main)
Placeholder for genetic_algorithm_v2: Framework for alternative implementations

## Possible Improvements
The algorithm can be further optimized by:
- Implementing parallel processing for fitness evaluation
- Using a more sophisticated selection method
- Adding additional mutation operators
- Implementing a local search algorithm to refine solutions
- Using a different representation for solutions when n >= 20
