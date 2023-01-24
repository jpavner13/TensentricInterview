#include <iostream>     /* read and write files */
using namespace std;
#include <cmath>        /* basic math */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "Hungarian.h"  /* Used to optimise puck movement */
#include "Puck.h"       /* Puck class */
#include <vector>       /* vectors */


// Ansi color code variables used to print command line in color
#define ESC "\033["
#define PURPLE_TXT "35"
#define RED_TXT "31"
#define GREEN_TXT "32"
#define LIGHT_BLUE_TXT "36"
#define RESET "\033[m"


/*  This fucntion creates a random instance of pucks, and returns the head of a doubly linked list containing a random number of created pucks.
    First it generates a random number between 1 and 9. It loops through for each puck and Initializes a puck instance and assigns
    each puck random x y cordinates in the plane. It then adds the puck onto the linked list and sets its prev and next variables to its
    adjacent nodes.
*/
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


/*  This fucntion itterates through each node in the given linked list and calls the classes
    printPuckInfo() function.
*/
void printPucks(Puck* head){
    Puck* currPuck = head;
    while(currPuck != NULL){
        currPuck->printPuckInfo();
        currPuck = currPuck -> next;
    }
}


/*      This fucntion is simmilar to the printPucs() function, with the main difference being that
        It prints a visualization of NULL pucks (the spaces on the plane that dont have a puck). 
*/
void printArrangedPucks(Puck* head, int numPucks){
    Puck* currPuck = head;
    int counter = 0;
    while(currPuck != NULL){
        currPuck->printArrangedPuckInfo();
        currPuck = currPuck -> next;
        counter++;
    }

    int xCords[9] = {420, 300, 180, 180, 300, 420, 420, 300, 180};
    int yCords[9] = {300, 300, 300, 180, 180, 180, 60, 60, 60};

    for(int i = counter; i < 9; i++){
        string color = PURPLE_TXT;
        cout << ESC << color << "m" << "======================================= NULL PUCK =======================================" << RESET << endl;
        cout << ESC << RED_TXT << "m" << "x Cordinate: " << RESET << xCords[i] << endl;
        cout << ESC << LIGHT_BLUE_TXT << "m" << "y Cordinate: " << RESET << yCords[i] << endl;
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


/*      This fucntion prints the menu of selections that will be displayed to the user when they run the program */
void printMenu(){
    cout << ESC << LIGHT_BLUE_TXT << "m" << "========= Menu =========" << RESET << endl;
    cout << ESC << RED_TXT << "m" << "1: " << RESET << "Run random test" << RESET << endl;
    cout << ESC << RED_TXT << "m" << "2: " << RESET << "Run manual test" << RESET << endl;
    cout << ESC << RED_TXT << "m" << "3: " << RESET << "Quit" << RESET << endl;
    cout << ESC << GREEN_TXT << "m" << "Enter number 1-3." << RESET << endl;
    return;
}


/*      This fucntion moves the pucks to their most optimal position on the x y plane. It takes two parameters: the head of the linked list
        containing the pucks in the given instance, as well as a vector of calculated most optimal positions on the plane for each puck. It
        itterates thorough each puck, finds its associated box and sets its cordinates to the center of the given box
*/
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


/*      This fucntion finds the distance between a puck and a given cordinate by using the pythagorean theorem. This is what populates the distance vector */
double getDistance(int xCord1, int xCord2, int yCord1, int yCord2){
    return (double(sqrt(((xCord1 - xCord2)*(xCord1 - xCord2)) + ((yCord1 - yCord2)*(yCord1 - yCord2)))));
}


/*      This fucntion returns a 2D vector of distances from each puck to each point on the plane. We use this vector to find the most optimal place to
        move each puck. It itterates through each random puck and calculates its distance to each point. It adds each distance to a vector. Once it calculates
        each point, it adds the vector to the 2D vector that will contain every puck and their distances to each point.
*/
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


/*      This function returns an ordered linked list of pucks representing the pucks in spaces 1-x where x is the number of pucks in the given 
        scenerio. Space 1 (the head of the returned linked list) is in the top right of the smaller square on the plane, and square 9 is in the
        bottom left of the smaller square with all of the points in between snaking horizontally in between those two points. It does this by 
        creating a vector of Pucks, itterating through each puck x amounts of times where x is the number of pucks in the given instance, and 
        pushes them to the back of the vector. This leaves us a vector of pucks in order of what space they are in. It then uses the vector of
        pucks and goes through each puck and sets their prev and next pointers to create a new linked list with the head being in space 1 and the
        tail being in space x (x = number of pucks). The parameters of thie equation are a pointer to the head of the unordered linked list and 
        the number of pucks in the given situation.
*/
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


/*      This function calls the work function of the given class instance and prints a message on success */
void work(Puck* puck){
    puck -> work();
    cout << "\nPuck " << puck -> getID() << " has worked." << endl;
}


/*      This function closes the gaps between a puck and NULL spaces after a puck does work(). The parameter is a pointer to an array of pointers
        to each puck in the current instance. It works by starting at the back of the array and finding the last not NULL place in the array. It
        Then sets the first NULL instance to point to the instance of the Puck that jsut finished work(). It also taked into account the edge case
        where there is only one puck. It checks to see if there is another puck. If there isnt, it moves the puck that just worked to the front of the
        array. There is no return value as the pointer to the array will edit the origional array passed into the fucntion.
*/
void closeGap(Puck* *puckArr){
    if(puckArr[0] == NULL){
        puckArr[0] = puckArr[8];
        puckArr[8] = NULL;
        return;
    } else {
        Puck* holder = puckArr[8];
        puckArr[8] = NULL;
        for(int i = 7; i >= 0; i--){
            if(puckArr[i] != NULL){
                puckArr[i + 1] = holder;
                return;
            } 
        }
    }
}


/*      This function prints the current location of each puck with the first puck being the one in space 1 and the last one being the puck
        in the last space (imidiatly after doing work). The spaces that are unoccupied are represneted with a NULL puck and arrow.
*/
void printList(Puck* *puckArr){
    for(int a = 0; a < 9; a++){
            if(puckArr[a] != NULL){
                cout << ESC << puckArr[a] -> getColor() << "m" << "Puck " << puckArr[a] -> getID() << " -----> " << RESET;
            } else {
                cout << ESC << "240" << "m" << "NULL -----> " << RESET;
            }
        }
}


/*      This function is the driver that calls all of the functions involved in doing work and moving all of the pucks through the plane. Its
        Parameters are a pointer to the head of the ordered linked list of Pucks (Must be the returned list from arrange()) and the number of
        pucks in the given scenario. It starts by adding each puck in the linked list into an array of Pucks in order of what space they 
        occupy. It then itterates through each puck in the current instance, calls work() on the leading puck, moves every other puck up in 
        position in the array, adds the puck that just worked to the back of the array then closes the gaps between pucks with NULL pucks.
        It also prints out the current state of the array between each step executed to visualize the process.
*/
void MoveAndPerformWork(Puck* head, int numPucks){
    Puck* puckArr[9] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
    Puck* currPuck = head;
    int counter = 0;
    while(currPuck != NULL){
        puckArr[counter] = currPuck;
        currPuck = currPuck -> next;
        counter++;
    }

    Puck* temp = puckArr[0];

    for(int i = 0; i < numPucks; i++){
        string color;
        switch (i % 4){
            case 0:
                color = PURPLE_TXT; 
                break;
            case 1:
                color = RED_TXT; 
                break;
            case 2:
                color = GREEN_TXT; 
                break;
            case 3:
                color = LIGHT_BLUE_TXT; 
                break;
            default:
                break;
        }
        puckArr[i] -> setColor(color);
    }

    printList(puckArr);

    for(int i = 0; i < numPucks; i++){
        cout << "\n\n\nWorking on Puck " << puckArr[0] -> getID() << ":" << endl;

        printList(puckArr);

        temp = puckArr[0];
        work(puckArr[0]);

        for(int j = 1; j < 9; j++){
            puckArr[j - 1] = puckArr[j];
            puckArr[j] = NULL;
        }
        puckArr[8] = temp;

        printList(puckArr);
        cout << endl;

        cout << "Closing gaps:" << endl;
        closeGap(puckArr);

        printList(puckArr);
    }

}


/*      This is the driver function that runs a random example and displays the process and results. It first creates a random instance
        of pucks and adds them to a linked list. It then counts the number of pucks in the instnace. It then passes the linked list into
        getDistanceVector() to obtain the vector of dinstances between each puck and each space. It then calls the Hungarian class instance
        to find the most optimal place to move each of the pucks to minimise movement distance. It then arranges the pucks into another
        linked list based on what space they are moved to, and finally preformes work and moves the pucks in the desired manner. It also
        prints the puck state between steps to help visualize what is occuring.
*/
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

    cout << "\nDistance Vector (in mm):" << endl;

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

    cout << "\n\nTotal movement distance: " << cost << " mm\n" << endl;

    move(head, choices);

    cout << "After moving puck state: " << endl;
    Puck* arrangedPucks = arrange(head, numPucks);
    printArrangedPucks(arrangedPucks, numPucks);

    cout << "Moving and preforming Work:" << endl;
    MoveAndPerformWork(arrangedPucks, numPucks);

    cout << "\n\n\nFinal Arrangement:" << endl;
    printArrangedPucks(arrangedPucks, numPucks);
}


/*      This function is very simmilar to createRandInstance() with the difference being that instead of generating random 
        numbers, it allows the user to manually enter the number of pucks and their locations to allow for easier testing of the
        program. It returns a pointer to the head of a doubly linked list of the Pucks initialized in the manually created instance.
*/
Puck* createManualInstance(){
    int numPucks;
    cout << "Enter number of Pucks: ";
    cin >> numPucks;
    cout << endl;

    Puck* head = NULL;
    Puck* prevPuck = NULL;

    for(int i = 0; i < numPucks; i++){
        int xCord, yCord;
        cout << "Enter x cordinate of puck " << i << ": ";
        cin >> xCord;
        cout << endl;
        cout << "Enter y cordinate of puck " << i << ": ";
        cin >> yCord;
        cout << endl;

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



/*      This is the driver function that runs a manual example and displays the process and results. It first creates a manual instance
        of pucks and adds them to a linked list. It then counts the number of pucks in the instnace. It then passes the linked list into
        getDistanceVector() to obtain the vector of dinstances between each puck and each space. It then calls the Hungarian class instance
        to find the most optimal place to move each of the pucks to minimise movement distance. It then arranges the pucks into another
        linked list based on what space they are moved to, and finally preformes work and moves the pucks in the desired manner. It also
        prints the puck state between steps to help visualize what is occuring.
*/
void runManual(){
    Puck* head = createManualInstance();

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

    cout << "Moving and preforming Work:" << endl;
    MoveAndPerformWork(arrangedPucks, numPucks);

    cout << "\n\n\nFinal Arrangement:" << endl;
    printArrangedPucks(arrangedPucks, numPucks);
}


/*      This is the driver function of the whole software. It continues to run until the user decides to quit. It allows the user
        to choose an option from the menu, and then calls the driver functions for each selection using a switch statement.
*/
int main(){
    srand (time(NULL));

    bool quit = false;

    while(!quit){
        printMenu();
        int choice;
        cin >> choice;

        switch (choice){
            case 1: {
                cout << "Running random test..." << endl;
                runRandom();
                cout << "Process Complete.\n\n" << endl;
                break;
            }
            case 2: {
                cout << "Running manual test..." << endl;
                runManual();
                cout << "Process Complete.\n\n" << endl;
                break;
            }
            case 3: {
                cout << "Quitting..." << endl;
                quit = true;
                break;
            }
            default: {
                cout << "Please enter a valid integer between 1 and 3." << endl;
                break;
            }
        }
    }
    return 0;
}