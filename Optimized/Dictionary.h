/*
 * Dictionary.h
 * by: Valerie Zhang
 * 
 * Purpose: The Dictionary class stores all the cities and their information 
 *          so it can be accessed easily
 */

#ifndef _DICTIONARY_H_
#define _DICTIONARY_H_

#include <fstream>
#include <functional>
#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <string>
#include <stack>
#include <regex>
#include <stdlib.h>

#include "SearchNode.h"

using namespace std;

static const int INITIAL_CAPACITY = 5000;

class Dictionary {
public:
    /* constructor, destructor: */
    Dictionary();
    Dictionary(string filename);
    ~Dictionary();

    /* setter: */
    void openAndParseFile(string filename);
    void setParent(string city, string parent);
    void setVisited(string city);
    void clear();
    
    /* getters: */
    SearchNode* getCityEntry(string name);
    bool inDictionary(string name);
    int size();
    void printCityInfo(string name);

private:
    int        capacity;
    int        numCities;
    SearchNode *table;
    
    ifstream infile;

    void parseFile();

    /* adding functions */
    void addCity(SearchNode City);
    void addNeighbor(string city1, string city2, double distance);

    /* maintaining the hashtable */
    void expand();
    void loadFactorCheck();

    /* hash functions */
    int hashIndex(string key);
    int linearProbeIndex(string key, int index);
};

#endif