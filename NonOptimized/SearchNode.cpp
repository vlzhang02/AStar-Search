/* 
 * SearchNode.cpp
 * By: Valerie Zhang June 2022
 *
 * Purpose: The SearchNode class stores all information of each city
 *
 */

#include "SearchNode.h"

using namespace std;

SearchNode::SearchNode() {
    name = "NULL";
    lat = lon = f = g = h = 0;
    parent = "NONE";
    visited = false;
}

SearchNode::SearchNode(string cityName, double latitude, double longitude) {
    name = cityName;
    lat = latitude;
    lon = longitude;
    f = g = h = 0;
    parent = "NONE";
    visited = false;
}
SearchNode::~SearchNode() {
    neighbors.clear();
}
/*
 * &operator=()
 * Purpose:     defines assignment operator to make a deep copy of the
 *              instance on the right hand side(rhs) into the instance on the
 *              left hand side(lhs)
 * Arguments:   reference to instance on the rhs
 * Returns:     reference to the lhs
 */
SearchNode &SearchNode::operator=(const SearchNode &other) {
    if (this == &other) {return *this;}
    // clear neighbors from this
    neighbors.clear();
    // initialized this with other's variable values
    name = other.name;
    lat = other.lat;
    lon = other.lon;
    f = other.f;
    g = other.g;
    h = other.h;
    parent = other.parent;
    visited = other.visited;
    // copy all neighbors
    for (size_t i = 0; i < other.neighbors.size(); i++) {
        neighbors.push_back(other.neighbors[i]);
    }

    return *this;
}
/* 
 * addNeigbor()
 * Purpose: add neighbor to neighbor vector
 * Parameters: neighbor name and distance between this and neighbor
 * Returns: none
 */
void SearchNode::addNeighbor(string city, double distance) {
    NeighborNode newNode;
    newNode.name = city;
    newNode.distance = distance;
    neighbors.push_back(newNode); 
}
/*  
 * getCityName()
 * Purpose: get city name
 * Parameters: none
 * Returns: city name
 */
string SearchNode::getCityName() {
    return name;
}
/*  
 * getLat()
 * Purpose: get city latitude
 * Parameters: none
 * Returns: city latitude
 */
double SearchNode::getLat() {
    return lat;
}
/*  
 * getLon()
 * Purpose: get city longitude
 * Parameters: none
 * Returns: city longitude
 */
double SearchNode::getLon() {
    return lon;
}
/*  
 * getF()
 * Purpose: get city f value
 * Parameters: none
 * Returns: city f value
 */
double SearchNode::getF() {
    return f;
}
/*  
 * getG()
 * Purpose: get city g value
 * Parameters: none
 * Returns: city g value
 */
double SearchNode::getG() {
    return g;
}
/*  
 * getH()
 * Purpose: get city h value
 * Parameters: none
 * Returns: city h value
 */
double SearchNode::getH() {
    return h;
}
/*  
 * getParent()
 * Purpose: get city's parent
 * Parameters: none
 * Returns: name of city's parent
 */
string SearchNode::getParent() {
    return parent;
}
/* 
 * getNeighbor()
 * Purpose: get name of neighbor at particular index
 * Parameters: index 
 * Returns: name of neighbor
 */
string SearchNode::getNeighbor(int index) {
    return neighbors[index].name;
}
/* 
 * getNeighborDistance()
 * Purpose: get distance between this and neighbor at particular index
 * Parameters: index 
 * Returns: distance
 */
double SearchNode::getNeighborDistance(int index) {
    return neighbors[index].distance;
}
/* 
 * getNeighborIndex()
 * Purpose: get index of a neighbor
 * Parameters: neighbor name
 * Returns: index
 */
int SearchNode::getNeighborIndex(string name) {
    for (size_t i = 0; i < neighbors.size(); i++) {
        if (neighbors[i].name == name) {
            return i;
        }
    }
    return 0;
}
/* 
 * getNumNeighbors()
 * Purpose: get number of neighbors of particular city
 * Parameters: none
 * Returns: number of neighbors
 */
int SearchNode::getNumNeighbors() {
    return neighbors.size();
}
/*
 * setH()
 * Purpose: set h of city
 * Parameters: h value
 * Returns: none
 */
void SearchNode::setH(double hVal) {
    h = hVal;
}
/*
 * setG()
 * Purpose: set g of city
 * Parameters: g value
 * Returns: none
 */
void SearchNode::setG(double gVal) {
    g = gVal;
}
/*
 * setF()
 * Purpose: set f of city
 * Parameters: f value
 * Returns: none
 */
void SearchNode::setF(double fVal) {
    f = fVal;
}
/*
 * setParent()
 * Purpose: set parent of city
 * Parameters: parent name
 * Returns: none
 */
void SearchNode::setParent(string name) {
    parent = name;
}
/*
 * setVisited()
 * Purpose: set city as visited
 * Parameters: none
 * Returns: none
 */
void SearchNode::setVisited() {
    visited = true;
}
/*
 * setUnvisited()
 * Purpose: set city as unvisited
 * Parameters: none
 * Returns: none
 */
void SearchNode::setUnvisited() {
    visited = false;
}
/*
 * isVisited()
 * Purpose: determine if city has been visited
 * Parameters: none
 * Returns: none
 */
bool SearchNode::isVisited() {
    return visited;
}
/*
 * printCityInfo()
 * Purpose: print city name, city latitude, and city longitude
 * Parameters: none
 * Returns: none
 */
void SearchNode::printCityInfo() {
    cout << name <<  " " << lat << " " << lon << "\n";
}

