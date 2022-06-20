/* 
 * SearchNode.h
 * Valerie Zhang June 2022
 * 
 * The SearchNode class stores all the information about a city needed
 * to perform A* search
 *
 */

#ifndef SEARCH_NODE_H
#define SEARCH_NODE_H

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

class SearchNode {

public: 
    SearchNode();
    SearchNode(string cityName, double latitude, double longitude);
    ~SearchNode();
    SearchNode &operator=(const SearchNode &other);

    void addNeighbor(string cityname, double distance);
    void setF(double fVal);
    void setG(double gVal);
    void setH(double hVal);
    void setVisited();
    void setUnvisited();
    void setParent(string name);

    string getCityName();
    double getLat();
    double getLon();
    double getF();
    double getG();
    double getH();
    string getParent();
    bool isVisited();
    string getNeighbor(int index);
    int getNeighborIndex(string name);
    double getNeighborDistance(int index);
    int getNumNeighbors();

    void printCityInfo();
private:
    struct NeighborNode {
        string name;
        double distance;
    };

    string name;
    double lat;
    double lon;
    double f;
    double g;
    double h;
    string parent;
    bool visited;
    vector<NeighborNode> neighbors;
};

#endif