// Class to generate a random maze using disjoint sets and print it in ASCII format to a file
// By Mary Elaine Califf and Devin Diaz
#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include <fstream>
using namespace std;

struct CellWalls
{
    bool south;
    bool east;
    CellWalls(bool startEast = true, bool startSouth = true) : east(startEast), south(startSouth) {}
};

class Maze
{
private:
    CellWalls *mazeWalls; // maze cells
    int numRows;
    int numColumns;

public:
    // constructor
    Maze(int rows, int cols);

    // copy constructor
    Maze(const Maze &orig) { copy(orig); };

    // destructor
    ~Maze() { delete [] mazeWalls; }

    // assignment operator
    Maze &operator=(const Maze &rhs);

    // generates the maze by randomly knocking down walls
    // stops generation once first and last value in the array are in the same set if stopEarly is true
    // stops generation once all values in the array are in the same set if stopEarly is false
    void generateMaze(bool stopEarly);

    // prints the maze to the specified outputStream
    void print(ostream &outputStream);

private:
    // private helper method to copy the data from another Maze object
    void copy(const Maze &orig);

    // private helper method for generateMaze() that determines the neighbor cell of randomly generated index
    // uses pass-by-reference to modify the neighbor variable which is declared in generateMaze()
    void findNeighbor(int randWall, int randIndex, int &neighbor);

    // private helper method for generateMaze() to knock down walls in the maze
    void breakWall(int randWall, int randIndex, int neighbor);
};

#endif
