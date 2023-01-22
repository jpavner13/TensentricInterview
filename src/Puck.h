#include <iostream>
using namespace std;

class Puck {
    public:
        Puck();                         // Initialize new puck instance
        Puck(int ID, int xPos, int Ypos, bool worked);

        bool getHasWorked();            // Return True if puck has worked, False if not has worked

        int getID();                    // Returns ID of puck instance
        int setID(int newID);                   // Sets ID of puck instance

        int getXCord();                 // Gets current X pos
        int setXCord(int newXCord);                // Sets/changes X cord. of puck instance
        int getYCord();                 // Gets current Y pos
        int setYCord(int newYCord);                // Sets/changes Y cord. of puck instance

        struct Puck* prev;
        struct Puck* next;

        void printPuckInfo();

    private:
        bool hasWorked;                 // Holds True if puck instnace has worked, False if puck instance has not worked
        int id;                         // Holds ID of puck instance
        int cord[2];                    // Array of current XY pos.
};