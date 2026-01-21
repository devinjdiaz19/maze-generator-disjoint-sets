// DisjointSet implementation using union by size and path compression
// By Mary Elaine Califf and Devin Diaz

#include "DisjointSet.h"
#include <iostream>

DisjointSet::DisjointSet(int numObjects)
{
    for (int i = 0; i < numObjects; i++) {
        theArray.push_back(-1);
    }
    numValues = numObjects;
}

//recursive method to find the item -- does path compression on the way out of the recursion
int DisjointSet::find(int objectIndex)
{
    if (theArray[objectIndex] < 0)
        return objectIndex;
    else
        return theArray[objectIndex] = find(theArray[objectIndex]);
}

bool DisjointSet::doUnion(int objIndex1, int objIndex2)
{
    int root1;
    int root2;

    if (objIndex1 < numValues && objIndex1 >= 0 && objIndex2 < numValues && objIndex2 >= 0) { // validate parameters
        root1 = find(objIndex1);
        root2 = find(objIndex2);
        if (root1 != root2) { // check that the two indexes aren't already in the same set
            if (theArray[root1] <= theArray[root2]) { // compare the sizes of the two sets
                theArray[root1] += theArray[root2];
                theArray[root2] = root1;
            }
            else {
                theArray[root2] += theArray[root1];
                theArray[root1] = root2;
            }
            if (-theArray[root1] == numValues || -theArray[root2] == numValues) // checks if union put all values in one set
                return true;
        }
    }

    return false;
}

void DisjointSet::printArrayValues(std::ostream &outputStream)
{
    for (int i = 0; i < numValues; i++)
    {
        outputStream << theArray[i] << " ";
    }
    outputStream << std::endl;
}
