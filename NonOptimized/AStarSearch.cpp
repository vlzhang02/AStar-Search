/* 
 * AStarSearch.cpp
 * By: Valerie Zhang June 2022
 *
 * Purpose: The AStarSearch class performs A* search 
 *
 *
 */

#include "AStarSearch.h"

using namespace std;

AStarSearch::AStarSearch() {
    nodesGenerated = 0;
    nodesLeft = 0;
    totalDistance = 0;
}

AStarSearch::AStarSearch(string filename) {
    nodesGenerated = 0;
    nodesLeft = 0;
    totalDistance = 0;
    cities.openAndParseFile(filename);
}

AStarSearch::~AStarSearch() {
    while (!frontier.empty()) {
        frontier.pop();
    }
}
/* 
 * isValid()
 * Purpose: checks if input is 0 or a valid city in dictionary
 * Parameters: input
 * Returns: true if valid, false if not
 */
bool AStarSearch::isValid(string input) {
    if (input == "0") {
        return true;
    } else {
        for (int i = 0; i < cities.size(); i++) {
            if (cities.inDictionary(input)) { // check if city is in dictionary
                return true;
            }
        }
    }
    return false;
}
/*
 * getStartCity()
 * Purpose: gets start city from user input
 * Parameters: none
 * Returns: string of start city
 */
string AStarSearch::getStartCity() {
    string input;
    cout << "Please enter name of start city (0 to quit): ";
    getline(cin, input);
    while (!isValid(input)) {
        cout << "City not valid. Please enter name of start city (0 to quit): ";
        getline(cin, input);
    }
    return input;
}
/*
 * getEndCity()
 * Purpose: gets end city from user input
 * Parameters: none
 * Returns: string of end city
 */
string AStarSearch::getEndCity() {
    string input;
    cout << "Please enter name of end city (0 to quit): ";
    getline(cin, input);
    while (!isValid(input)) {
        cout << "City not valid. Please enter name of end city (0 to quit): ";
        getline(cin, input);
    }
    return input;
}
/*
 * loop)
 * Purpose: loops entire program until user enters 0
 * Parameters: none
 * Returns: none
 */
void AStarSearch::loop() {
    string start = getStartCity();
    if (start == "0") {
        cout << "\nGoodbye.\n";
        exit(EXIT_SUCCESS);
    }
    string end = getEndCity();
    if (end == "0") {
        cout << "\nGoodbye.\n";
        exit(EXIT_SUCCESS);
    }
    cout << "\nSearching for path from " << start << " to " << end << "...\n";
    printSearch(start, end);
    reset(); // resets frontier, dictionary, and member variables
    return;
}
/*
 * run()
 * Purpose: prints out prompt to run program again after search is complete
 * Parameters: none
 * Returns: None
 */
void AStarSearch::run() {
    string input = "";
    while (input != "0") {
        loop();
        cout << "------------------------------------\n";
        cout << "Enter 0 to quit, or any other keys to search again: ";
        getline(cin, input);
        cout << "------------------------------------\n";
    }
    cout << "Goodbye.\n";
    return;
}
/*
 * search()
 * Purpose: performs astar search
 * Parameters: string of start and end city
 * Returns: true if path found, false if not
 */
bool AStarSearch::search(string start, string goal) {
    // initialize frontier and path queue
    cities.setParent(start, start); // sets start parent to self
    cities.setVisited(start); // sets self to visited
    SearchNode *sn = cities.getCityEntry(start); 
    SearchNode *end = cities.getCityEntry(goal);
    fNode begin = {sn->getCityName(), sn->getCityName(), 0, 0}; // initialized fNode
    frontier.push(begin); // add to frontier
    nodesGenerated++;

    while (!frontier.empty()) {
        fNode current = frontier.top(); // get node with lowest f
        frontier.pop();       // pop off queue
        if (current.name == goal) { //check if is goal
            goalFoundOperations(current, goal);
            return true;
        }
        addNeighbors(current, end);
        // sets F, G, and parent in dictionary if not expanded already
        if (!cities.getCityEntry(current.name)->isVisited()) { 
            updateDictionary(current);
        }
    }
    // if path isn't found
    nodesLeft = 0;
    totalDistance = -1;
    return false;
}
/*
 * printSearch() 
 * Purpose: print search reseults 
 * Parameters: start and end city
 * Returns: None
 */
void AStarSearch::printSearch(string start, string end) {
    if ((start == end) or (search(start, end))) {
        cout << "Target found: ";
        cities.printCityInfo(end);
        cout << "\nRoute found: ";
        if (start == end) {
            cout << "Started at goal; no travel necessary!\n";
        } else {
            // print path
            while (!path.empty()) {
                cout << path.top();
                path.pop();
                if (!path.empty()) {
                    cout << " -> ";
                }
            }
            cout << "\n";
        }
    } else {
        cout << "NO PATH\n";
    } 
    // print total distance, nodes generated, nodes left in frontier
    cout << setprecision(1) << fixed;
    cout << "Distance: " << totalDistance << "\n\n";
    cout << "Total node generated: " << nodesGenerated << "\n";
    cout << "Nodes left in frontier: " << nodesLeft << "\n\n";
}
/*
 * getHVal()
 * Purpose: calculate distance between a city and the goal
 * Parameters: latitudes and longitudes of both cities
 * Returns: double of h
 */
double AStarSearch::getHVal(double lat1, double lon1, double goalLat, double goalLon) {
    lat1 = lat1 * M_PI/180;
    goalLat = goalLat * M_PI/180;
    double dlat = goalLat - lat1;
    double dlon = (goalLon * M_PI/180) - (lon1 * M_PI/180);
    double a = pow(sin(dlat/2), 2) + cos(lat1) * cos(goalLat) * pow(sin(dlon/2), 2);
    double c = 2 * atan2(sqrt(a), sqrt((1-a)));
    double H = 3961 * c;
    return H;
}
/*
 * getPath()
 * Purpose: gets path from start to goal using a stack
 * Parameters: name of goal city
 * Returns: none
 */
void AStarSearch::getPath(string goal) {
    SearchNode *temp = cities.getCityEntry(goal);
    while (temp->getParent() != temp->getCityName()) {
        path.push(temp->getCityName());
        temp = cities.getCityEntry(temp->getParent());
    }
    path.push(temp->getCityName());
}
/*
 * reset()
 * Purpose: resets program to start stat
 * Parameters: none
 * Returns: none
 */
void AStarSearch::reset() {
    // empties frontier
    while (!frontier.empty()) {
        frontier.pop();
    }
    // reset search info variables
    nodesGenerated = totalDistance = nodesLeft = 0;
    cities.clear(); // clear dictionary
}
/*
 * goalFoundOperations()
 * Purpose: perform operations when goal is found
 * Parameters: current fNode, name of goal
 * Returns: non
 */
void AStarSearch::goalFoundOperations(fNode current, string goal) {
    // sets goal's parent as current
    cities.setParent(current.name, current.parent); 
    totalDistance = current.g; // update totalDistance
    nodesLeft = frontier.size();
    getPath(goal); // get path
}
/*
 * updateDictionary()
 * Purpose: update city entry with fNode info(parent, f, g) and set as visited
 * Parameters: fNode
 * Returns: none
 */
void AStarSearch::updateDictionary(fNode current) {
    SearchNode *set = cities.getCityEntry(current.name);
    set->setVisited(); // set visited
    set->setF(current.f); // set f
    set->setG(current.g); // set g
    set->setParent(current.parent); // set parent
}
/*  
 * addNeighbors()
 * Purpose: adds all neighbors of fNode to frontier
 * Parameters: current fNode, pointer to goal's city entry
 * Returns: none
 */
void AStarSearch::addNeighbors(fNode current, SearchNode* end) {
    int numNeighbors = cities.getCityEntry(current.name)->getNumNeighbors();
    SearchNode *curr = cities.getCityEntry(current.name);
    for (int i = 0; i < numNeighbors; i++) { // for each neighbor
        SearchNode *s = cities.getCityEntry(curr->getNeighbor(i)); // getting neighbor entry
        if (cities.getCityEntry(s->getCityName())->getH() == 0) { // set h if not set
            s->setH(getHVal(s->getLat(), s->getLon(), end->getLat(), end->getLon()));
        }
        // initialize fNode
        fNode toAdd = {s->getCityName(), // initialize new fNode
                        current.name, current.g + curr->getNeighborDistance(i),
                        toAdd.g + s->getH()};
        frontier.push(toAdd); // add to frontier
        nodesGenerated++;
    } 
}
