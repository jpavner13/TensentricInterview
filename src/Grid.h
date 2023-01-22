#include <iostream>
using namespace std;

class Grid {
    public:
        Grid();

        bool isOccupied(int xCord, int yCord);

        int getXCord(int xCord, int yCord);
        int getYCord(int xCord, int yCord);

        int getNumPucks();
        int setNumPucks(int numPucks);

    private:
        bool map[4][4];
        int numPucks;
};