#include <iostream>     /* read and write files */
using namespace std;
#include <cmath>        /* basic math */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "Hungarian.h"
#include <vector>

#include "Puck.h"

#define ESC "\033["
#define PURPLE_TXT "35"
#define RED_TXT "31"
#define GREEN_TXT "32"
#define LIGHT_BLUE_TXT "36"
#define RESET "\033[m"

Puck* createRandInstance(){
    int numPucks = rand() % 9 + 1;

    cout << numPucks << " pucks were created." << endl;

    Puck* head = NULL;
    Puck* prevPuck = NULL;

    for(int i = 0; i < numPucks; i++){
        int xCord = rand() % 480 + 1;
        int yCord = rand() % 480 + 1;
        
        if(head == NULL){
            head = new Puck(i, xCord, yCord, false);
            prevPuck = head;
        } else {
            Puck* newPuck = new Puck(i, xCord, yCord, false);
            prevPuck -> next = newPuck;
            newPuck -> prev = prevPuck;
            prevPuck = newPuck;
        }
    }

    return head;
}

void printPucks(Puck* head){
    Puck* currPuck = head;
    while(currPuck != NULL){
        currPuck->printPuckInfo();
        currPuck = currPuck -> next;
    }
}

void printArrangedPucks(Puck* head, int numPucks){
    Puck* currPuck = head;
    int counter = 0;
    while(currPuck != NULL){
        currPuck->printArrangedPuckInfo();
        currPuck = currPuck -> next;
        counter++;
    }

    for(int i = counter; i < 9; i++){
        string color = PURPLE_TXT;
        cout << ESC << color << "m" << "======================================= NULL PUCK =======================================" << RESET << endl;
        cout << ESC << RED_TXT << "m" << "x Cordinate: " << RESET << "NULL" << endl;
        cout << ESC << LIGHT_BLUE_TXT << "m" << "y Cordinate: " << RESET << "NULL" << endl;
        cout << ESC << GREEN_TXT << "m" << "Has Worked?: " << RESET << "NULL" << endl;
        

        cout << ESC << color << "m" << "=======================================================================================" << RESET << endl;
        if(i + 1 != 9){
            cout << ESC << color << "m" << "                                                              |   |     " << RESET << endl;
            cout << ESC << color << "m" << "                                                            \\       /   " << RESET << endl;
            cout << ESC << color << "m" << "                                                             \\     /    " << RESET << endl;
            cout << ESC << color << "m" << "                                                              \\   /     " << RESET << endl;
            cout << ESC << color << "m" << "                                                               \\ /      " << RESET << endl;
        } else {
            cout << endl << endl;
        }
    }
    return;
}

void printMenu(){
    cout << ESC << LIGHT_BLUE_TXT << "m" << "========= Menu =========" << RESET << endl;
    cout << ESC << RED_TXT << "m" << "1: " << RESET << "Run random test" << RESET << endl;
    cout << ESC << RED_TXT << "m" << "2: " << RESET << "Run manual test" << RESET << endl;
    cout << ESC << RED_TXT << "m" << "3: " << RESET << "Quit" << RESET << endl;
    cout << ESC << GREEN_TXT << "m" << "Enter number 1-3." << RESET << endl;
    return;
}

void move(Puck* head, vector<int> choices){
    int xCords[9] = {420, 300, 180, 180, 300, 420, 420, 300, 180};
    int yCords[9] = {300, 300, 300, 180, 180, 180, 60, 60, 60};
    int spaces[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    int counter = 0;
    Puck* temp = head;

    while(temp != NULL){
        int space = choices[counter];
        temp->setXCord(xCords[space]);
        temp->setYCord(yCords[space]);
        temp->setSpace(spaces[space]);
        temp = temp->next;
        counter++;
    }
}

double getDistance(int xCord1, int xCord2, int yCord1, int yCord2){
    return (double(sqrt(((xCord1 - xCord2)*(xCord1 - xCord2)) + ((yCord1 - yCord2)*(yCord1 - yCord2)))));
}

vector<vector<double>> getDistanceVector(Puck* head, int numPucks){
    vector<vector<double>> distanceVector;

    Puck* currPuck = head;

    int xCords[9] = {420, 300, 180, 180, 300, 420, 420, 300, 180};
    int yCords[9] = {300, 300, 300, 180, 180, 180, 60, 60, 60};


    for(int i = 0; i < numPucks; i++){
        vector<double> currVect;
        for(int j = 0; j < numPucks; j++){
            int puckXCord = currPuck->getXCord();
            int puckYCord = currPuck->getYCord();
            currVect.push_back(getDistance(puckXCord, xCords[j], puckYCord, yCords[j]));
        }
        distanceVector.push_back(currVect);
        currPuck = currPuck -> next;
    }

    return distanceVector;
}

Puck* arrange(Puck* head, int numPucks){
    Puck* currPuck = head;
    Puck* tempPuck = NULL;
    Puck* recPuc = NULL;

    vector<Puck*> pucks;

    int counter = 0;

    for(int i = 0; i <= numPucks; i++){
        while(currPuck != NULL){
            if(currPuck -> getSpace() == i){
                pucks.push_back(currPuck);
                currPuck = currPuck -> next;
            } else {
                currPuck = currPuck -> next;
            }
        }
        currPuck = head;
    }

    for(int i = 0; i < numPucks; i++){
        if(i == 0){
            pucks[i] -> prev = NULL;
            pucks[i] -> next = pucks[i+1];
        } else if (i == numPucks - 1){
            pucks[i] -> prev = pucks[i - 1];
            pucks[i] -> next = NULL;
        } else {
            pucks[i] -> prev = pucks[i - 1];
            pucks[i] -> next = pucks[i + 1];
        }
    }

    tempPuck = pucks[0];
    return tempPuck;
}

void runRandom(){
    Puck* head = createRandInstance();

    cout << "Initial state of pucks: " << endl;
    printPucks(head);

    Puck* counter = head;
    int numPucks = 0;
    while(counter != NULL){
        numPucks++;
        counter = counter -> next;
    }

    vector<vector<double>> distanceVector = getDistanceVector(head, numPucks);

    cout << "\nDistance Vector:" << endl;

    for(int i = 0; i < numPucks; i++){
        for(int j = 0; j < numPucks; j++){
            cout << distanceVector[i][j] << "\t" ;
        }
        cout << endl;
    }

    HungarianAlgorithm algo;
    vector<int> choices;

    double cost = algo.Solve(distanceVector, choices);

    cout << "\nOptimal Puck-Space movement Vector:" << endl;

    for (int x = 0; x < distanceVector.size(); x++){
		cout << x << "," << choices[x] << "\t";
    }

    cout << "\n\nTotal movement distance: " << cost << "\n" << endl;

    move(head, choices);

    cout << "After moving puck state: " << endl;
    Puck* arrangedPucks = arrange(head, numPucks);
    printArrangedPucks(arrangedPucks, numPucks);
}

int main(){
    srand (time(NULL));

    printMenu();
    int choice;
    cin >> choice;

    switch (choice){
        case 1: {
            runRandom();
            break;
        }
        case 2: {
            cout << "Case 2" << endl;
            break;
        }
        case 3: {
            cout << "Case 3" << endl;
            break;
        }
        default: {
            break;
        }
    }
    return 0;
}