# Maze Generator Using Disjoint Sets

## Overview
This project generates a random maze using the disjoint set (union-find) data structure.
The maze generation stops early once the start and end cells are connected, producing a
simpler and more readable maze.

## Concepts Used
- Disjoint Sets (Union-Find)
- Randomized Algorithms
- Graph Connectivity
- C++

## How It Works
- Each cell starts in its own set
- Random walls are removed by unioning sets
- Generation stops once start and end nodes are connected

## How to Run
g++ DisjointSet.cpp Maze.cpp MazeGenerator.cpp
./a.out
