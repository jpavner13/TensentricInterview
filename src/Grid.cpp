#include "Grid.h"
#include <iostream>

using namespace std;

Grid::Grid(){}

bool Grid::isOccupied(int xCord, int yCord){
    return map[xCord][yCord];
}

int Grid::getNumPucks(){
    return numPucks;
}

int Grid::setNumPucks(int pucks){
    bool success;
    if(pucks > 0 && pucks < 10){
        numPucks = pucks;
        success = true;
    } else {
        success = false;
        cout << "Error setting number of pucks on grid" << endl;
    }

    if(success) {
        return numPucks;
    } else {
        return -1;
    }
}