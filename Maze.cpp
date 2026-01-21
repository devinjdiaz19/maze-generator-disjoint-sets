// Implementation of Maze class
// By Mary Elaine Califf and Devin Diaz

#include "Maze.h"
#include "DisjointSet.h"
using namespace std;

Maze::Maze(int rows, int cols)
{
    numRows = rows;
    numColumns = cols;
    int numCells = rows * cols;
    mazeWalls = new CellWalls[numCells];
    mazeWalls[numCells - 1].east = false;
}

Maze &Maze::operator=(const Maze &rhs)
{
    if (this != &rhs)
    {
        delete [] mazeWalls;
        this->copy(rhs);
    }
    return *this;
}

void Maze::generateMaze(bool stopEarly)
{
    int numCells = numRows * numColumns;
    DisjointSet mySet(numCells);
    bool mazeComplete = false;

    while (!mazeComplete) {
        int randIndex = rand() % numCells;
        int randWall = rand() % 4;
        int neighbor = randIndex;

        findNeighbor(randWall, randIndex, neighbor);

        // only breaks wall and union if the two cells aren't in the same set
        if (mySet.find(randIndex) != mySet.find(neighbor)) {
            breakWall(randWall, randIndex, neighbor);
            mazeComplete = mySet.doUnion(randIndex, neighbor);

            if (stopEarly) // makes mazeComplete true once first and last values in array are in same set
                mazeComplete = mySet.find(0) == mySet.find(numCells - 1);
        }
    }
}

void Maze::print(ostream &outputStream)
{
    // print the top row of walls
    for (int i = 0; i < numColumns; i++)
        outputStream << " _";
    outputStream << '\n';
    for (int i = 0; i < numRows; i++)
    {
        int cellbase = i * numColumns;
        // print west wall (except at entrance)
        if (i == 0)
            outputStream << ' ';
        else
            outputStream << '|';
        for (int j = 0; j < numColumns; j++)
        {
            if (mazeWalls[cellbase + j].south)
                outputStream << '_';
            else
                outputStream << ' ';
            if (mazeWalls[cellbase + j].east)
                outputStream << '|';
            else
                outputStream << ' ';
        }
        outputStream << '\n';
    }
}

void Maze::copy(const Maze &orig)
{
    this->numRows = orig.numRows;
    this->numColumns = orig.numColumns;
    int numCells = numRows * numColumns;
    mazeWalls = new CellWalls[numCells];
    for (int i = 0; i < numCells; i++)
    {
        this->mazeWalls[i] = orig.mazeWalls[i];
    }
}

void Maze::findNeighbor(int randWall, int randIndex, int &neighbor) 
{
    int row = randIndex / numColumns;
    int col = randIndex % numColumns;

    if (randWall == 0 || randWall == 2) { // going left or right
        // checks if neighbor exists in the direction we're going, goes opposite direction as needed
        if ((randWall == 0 && col == 0) || (randWall == 2 && col < numColumns - 1))
            neighbor++;
        else
            neighbor--;
    }
    if (randWall == 1 || randWall == 3) { // going down or up
        // checks if neighbor exists in the direction we're going, goes opposite direction as needed
        if ((randWall == 1 && row == numRows - 1) || (randWall == 3 && row > 0))
            neighbor -= numColumns;
        else
            neighbor += numColumns;
    }
}

void Maze::breakWall(int randWall, int randIndex, int neighbor) {
    if (randWall == 0 || randWall == 2) // break east wall of whichever index comes first in the array
        mazeWalls[(neighbor < randIndex) ? neighbor : randIndex].east = false;
    else // break south wall of whichever index comes first in the array
        mazeWalls[(neighbor < randIndex) ? neighbor : randIndex].south = false;
}