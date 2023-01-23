#include "Puck.h"
#include <iostream>

using namespace std;

Puck::Puck(){}

Puck::Puck(int ID, int xPos, int yPos, bool worked){
    id = ID;
    cord[0] = xPos;
    cord[1] = yPos;
    hasWorked = worked;
    prev = NULL;
    next = NULL;
}

bool Puck::getHasWorked(){
    return hasWorked;
}

void Puck::work(){
    hasWorked = true;
}

int Puck::getID(){
    return id;
}

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

int Puck::getXCord(){
    return cord[0];
}

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

int Puck::getYCord(){
    return cord[1];
}

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

#define ESC "\033["
#define PURPLE_TXT "35"
#define RED_TXT "31"
#define GREEN_TXT "32"
#define LIGHT_BLUE_TXT "36"
#define RESET "\033[m"

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

void Puck::setSpace(int newSpace){
    space = newSpace;
}

int Puck::getSpace(){
    return space;
}

string Puck::getColor(){
    return color;
}

void Puck::setColor(string newColor){
    color = newColor;
    return;
}