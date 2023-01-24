#include "Puck.h"
#include <iostream>

using namespace std;


/*      Undefined constructor */
Puck::Puck(){
    prev = NULL;
    next = NULL;
}


/*      Defined constructor */
Puck::Puck(int ID, int xPos, int yPos, bool worked){
    id = ID;
    cord[0] = xPos;
    cord[1] = yPos;
    hasWorked = worked;
    prev = NULL;
    next = NULL;
}


/*      Returns true if puck has worked, false if puck has not worked */
bool Puck::getHasWorked(){
    return hasWorked;
}


/*      Sets hasWorked to true after the puck has done work */
void Puck::work(){
    hasWorked = true;
}


/*      Returns the puck ID. The Puck ID is the order in wich the pucks were created */
int Puck::getID(){
    return id;
}


/*      Sets the puck ID. Returns newID if it was successful, returns -1 if ID was out of bounds or if there was an error */
int Puck::setID(int newID){
    bool success;
    if(newID > 0 && newID < 10){
        id = newID;
        success = true;
    } else {
        success = false;
        cout << "Invalid puck ID. Check that puck ID is in range." << endl;
    }

    if(id == newID){
        success = true;
    } else {
        success = false;
        cout << "Failed to set puck ID." << endl;
    }

    if(success){
        return newID;
    } else {
        return -1;
    }
}


/*      Returns current x cordinate of the puck */
int Puck::getXCord(){
    return cord[0];
}


/*      Sets new x cordinate of puck. Returns newCord if it was successful, returns -1 if cord was out of bounds or if there was an error */
int Puck::setXCord(int newCord){
    bool success;

    if(newCord >= 0 && newCord <= 480){
        cord[0] = newCord;
        success = true;
    } else {
        success = false;
        cout << "Tried to set an out of range X cordinate." << endl;
    }

    if(cord[0] == newCord){
        success = true;
    } else {
        success = false;
        cout << "Failed to set puck X cordinate." << endl;
    }

    if(success){
        return newCord;
    } else {
        return -1;
    }
}


/*      Returns current y cordinate of the puck */
int Puck::getYCord(){
    return cord[1];
}


/*      Sets new y cordinate of puck. Returns newCord if it was successful, returns -1 if cord was out of bounds or if there was an error */
int Puck::setYCord(int newCord){
    bool success;

    if(newCord >= 0 && newCord <= 480){
        cord[1] = newCord;
        success = true;
    } else {
        success = false;
        cout << "Tried to set an out of range Y cordinate." << endl;
    }

    if(cord[1] == newCord){
        success = true;
    } else {
        success = false;
        cout << "Failed to set puck Y cordinate." << endl;
    }

    if(success){
        return newCord;
    } else {
        return -1;
    }
}


// Ansi color code variables used to print command line in color
#define ESC "\033["
#define PURPLE_TXT "35"
#define RED_TXT "31"
#define GREEN_TXT "32"
#define LIGHT_BLUE_TXT "36"
#define RESET "\033[m"


/*      Prints the current Puck's info to the command line in a way that is easily read by the user */
void Puck::printPuckInfo(){
    string color = PURPLE_TXT;
    cout << ESC << color << "m" << "======================================= Puck " << id << " =======================================" << RESET << endl;
    cout << ESC << RED_TXT << "m" << "x Cordinate: " << RESET << cord[0] << endl;
    cout << ESC << LIGHT_BLUE_TXT << "m" << "y Cordinate: " << RESET << cord[1] << endl;
    cout << ESC << GREEN_TXT << "m" << "Has Worked?: " << RESET << hasWorked << endl;
    

    cout << ESC << color << "m" << "=======================================================================================" << RESET << endl;
    if(next != NULL){
        cout << ESC << color << "m" << "                                                              |   |     " << RESET << endl;
        cout << ESC << color << "m" << "                                                            \\       /   " << RESET << endl;
        cout << ESC << color << "m" << "                                                             \\     /    " << RESET << endl;
        cout << ESC << color << "m" << "                                                              \\   /     " << RESET << endl;
        cout << ESC << color << "m" << "                                                               \\ /      " << RESET << endl;
    } else {
        cout << endl << endl;
    }
    return;
}


/*      Prints the current Puck's info to the command line in a way that is easily read by the user. This is used to solve edge case of there being 9 pucks */
void Puck::printArrangedPuckInfo(){
    string color = PURPLE_TXT;
    cout << ESC << color << "m" << "======================================= Puck " << id << " =======================================" << RESET << endl;
    cout << ESC << RED_TXT << "m" << "x Cordinate: " << RESET << cord[0] << endl;
    cout << ESC << LIGHT_BLUE_TXT << "m" << "y Cordinate: " << RESET << cord[1] << endl;
    cout << ESC << GREEN_TXT << "m" << "Has Worked?: " << RESET << hasWorked << endl;
    

    cout << ESC << color << "m" << "=======================================================================================" << RESET << endl;
    if(id != 9){
        cout << ESC << color << "m" << "                                                              |   |     " << RESET << endl;
        cout << ESC << color << "m" << "                                                            \\       /   " << RESET << endl;
        cout << ESC << color << "m" << "                                                             \\     /    " << RESET << endl;
        cout << ESC << color << "m" << "                                                              \\   /     " << RESET << endl;
        cout << ESC << color << "m" << "                                                               \\ /      " << RESET << endl;
    } else {
        cout << endl << endl;
    }
    return;
}


/*      Sets the space number to the given space */
void Puck::setSpace(int newSpace){
    space = newSpace;
}


/*      Returns the current pucks space number */
int Puck::getSpace(){
    return space;
}


/*      Returns the ANSI color code of the current puck */
string Puck::getColor(){
    return color;
}


/*      Sets the current pucks color to the given ANSI color code */
void Puck::setColor(string newColor){
    color = newColor;
    return;
}