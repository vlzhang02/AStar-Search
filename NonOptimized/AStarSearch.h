/* 
 * AStarSearch.h
 * By: Valerie Zhang
 *
 * Purpose: Perform A* search between two cities inputed from user
 *
 */

#ifndef A_STAR_SEARCH
#define A_STAR_SEARCH

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <queue>
#include <string>
#include <stack>
#include <regex>
#include <stdlib.h>
#include <limits>

#include "SearchNode.h"
#include "Dictionary.h"
using namespace std;

static const double R = 3961;

struct fNode{
    string name;
    string parent;
    double g;
    double f;
};

struct CompareF {
    bool operator () (const fNode& n1, const fNode& n2) {
        return -n1.f < -n2.f;
    }
};

class AStarSearch {
public:
    AStarSearch();
    AStarSearch(string filename);
    ~AStarSearch();
    
    void run();

private:
    int nodesGenerated;
    size_t nodesLeft;
    double totalDistance;

    Dictionary cities;
    priority_queue<fNode, vector<fNode>, CompareF> frontier;
    stack<string> path;

    void openFile(string filename);
    void parseFile();

    void loop();
    bool search(string start, string goal);
    bool isValid(string city);
    void insert(SearchNode node);
    void goalFoundOperations(fNode current, string goal);
    void updateDictionary(fNode current);
    void reset();

    string getStartCity();
    string getEndCity();
    double getHVal(double lat1, double lon1, double goalLat, double goalLon);
    void getPath(string goal);

    void printSearch(string start, string end);
    void addNeighbors(fNode current, SearchNode* end);
    
};

#endif
