#include <iostream>
using namespace std;

class Puck {
    public:
        Puck();                         // Initialize new puck instance
        Puck(int ID, int xPos, int Ypos, bool worked);

        bool getHasWorked();            // Return True if puck has worked, False if not has worked
        void work();

        int getID();                    // Returns ID of puck instance
        int setID(int newID);                   // Sets ID of puck instance

        int getXCord();                 // Gets current X pos
        int setXCord(int newXCord);                // Sets/changes X cord. of puck instance
        int getYCord();                 // Gets current Y pos
        int setYCord(int newYCord);                // Sets/changes Y cord. of puck instance

        struct Puck* prev;              // Pointer to the next puck in a linked list
        struct Puck* next;              // Pointer to the previous puck in a doubly linked list

        void printPuckInfo();           // Prints the pucks information to be easily read in the terminal by the user
        void printArrangedPuckInfo();   // Prints the pucks information to be easily read in the terminal by the user. 
                                            //This solves the edge case of there being 9 pucks.

        void setSpace(int newSpace);    // Sets the number 1-9 to represent the space that the puck is assigned to
        int getSpace();                 // Returns the current space of the puck insance

        string getColor();
        void setColor(string newColor);

    private:
        bool hasWorked;                 // Holds True if puck instnace has worked, False if puck instance has not worked
        int id;                         // Holds ID of puck instance
        int cord[2];                    // Array of current XY pos.
        int space = -1;                 // Holds the number of the space the puck is in. Holds -1 if no space is yet assigned
        string color = "";              // Holds the ANSI color code of the current puck, used for printing to terminal in color
};