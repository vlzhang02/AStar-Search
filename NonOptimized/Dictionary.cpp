/* 
 * Dictionary.cpp
 * by: Valerie Zhang
 *
 * Purpose: The Dictionary class stores all the cities and their information
 *
 */

#include "Dictionary.h"

using namespace std;

Dictionary::Dictionary() {
    capacity = INITIAL_CAPACITY;

    table          = new SearchNode[capacity]; // table is a pointer
    SearchNode start;
    for (int i = 0; i < capacity; i++) {
        table[i] = start;
    }
    numCities = 0;
}

Dictionary::Dictionary(string filename) {
    capacity = INITIAL_CAPACITY;

    table          = new SearchNode[capacity]; // table is a pointer
    SearchNode start;
    for (int i = 0; i < capacity; i++) {
        table[i] = start;
    }
    numCities = 0;
    openAndParseFile(filename);
}

Dictionary::~Dictionary() {
    delete [] table;
    table = nullptr;
    numCities = 0;
}
/* 
 * openAndParseFile()
 * Purpose: opens and parses file
 * Parameters: filename
 * Returns: none
 */
void Dictionary::openAndParseFile(string filename){
    infile.open(filename);
    if (!infile.is_open()) {
        cerr << "Error: could not open " << filename << "\n";
    }
    parseFile();
    infile.close();
}
/* 
 * parseFile()
 * Purpose: parse file for city info, its neighbors, and the distance between them
 * Paramter: none
 * Returns: none
 */
void Dictionary::parseFile() {
    regex cityData("(.+) (-*\\d+\\.\\d+) (-*\\d+\\.\\d+)"); // name, lat, lon
    regex cityDistance("(.+), (.+): (\\d+\\.\\d+)"); // name, name: distance
    string line = "";

    cerr << "Reading city data... ";
    while (getline(infile, line)) {
        smatch sm1;
        smatch sm2;
        if (regex_search(line, sm1, cityData)) { // check against 1st regex
            // initialize and add city to dictionary
            SearchNode toAdd(sm1[1], stof(sm1[2]), stof(sm1[3]));
            addCity(toAdd);
        } else if (regex_search(line, sm2, cityDistance)) { // check against 2nd regex
            double distance = stof(sm2[3]); // convert distance to fload
            addNeighbor(sm2[1], sm2[2], distance); // add to dictionary
        } else { // for lines starting with #
            continue;
        }
    }
    cerr << "Done.\n\n"; 
    cerr << "Number of cities: " << numCities << "\n";
}

/** *****************************************************************\
*                     hashtable getting functions                    *
\********************************************************************/
/* 
 * getCityEntry()
 * Purpose: get pointer to city's entry in dictionary
 * Parameters: city name
 * Returns: pointer to city entry in dictionary
 */
SearchNode* Dictionary::getCityEntry(string name) {
    return &(table[linearProbeIndex(name, hashIndex(name))]);
}
/*
 * getCity()
 * Purpose: determine if city is in dictionary
 * Parameters: city name
 * Returns: true if in dictionary, false if not
 */
bool Dictionary::inDictionary(string name) {
    if (table[linearProbeIndex(name, hashIndex(name))].getCityName() == name) {
        return true;
    }
    return false;
}
/* 
 * size()
 * Purpose: get size of dictionary
 * Parameters: node
 * Returns: number of cities in dictionary
 */
int Dictionary::size() {
    return numCities;
}
/* 
 * printCityInfo()
 * Purpose: prints city info of a particular entry
 * Parameters: city name
 * Returns: None
 */
void Dictionary::printCityInfo(string name) {
    table[linearProbeIndex(name, hashIndex(name))].printCityInfo();
}

/** *****************************************************************\
*                     hashtable setting functions                    *
\********************************************************************/
/* 
 * setParent()
 * Purpose: sets parent in city's dictionary entry
 * Parameters: strings of city and it's parent
 * Returns: None
 */
void Dictionary::setParent(string city, string parent) {
    table[linearProbeIndex(city, hashIndex(city))].setParent(parent);
}
/* 
 * setVisited()
 * Purpose: sets city as visited in dictionary
 * Parameters: string of city name
 * Returns: None
 */
void Dictionary::setVisited(string city) {
    table[linearProbeIndex(city, hashIndex(city))].setVisited();
}
/* 
 * clear()
 * Purpose: resets dictionary for new search
 * Parameters: None
 * Returns: None
 */
void Dictionary::clear() {
    for (int i = 0; i < capacity; i++) {
        if (table[i].isVisited()) { // resets visited cities
            table[i].setF(0);
            table[i].setG(0);
            table[i].setH(0);
            table[i].setParent("NONE");
            table[i].setUnvisited();
        } else if (table[i].getH() != 0) { // resets cities with nonzero h
            table[i].setH(0);
        }
    }
}

/* 
 * addCity()
 * Parameters: SearchNode instance
 * Purpose: adds city to dictionary
 * Returns: none
 */
void Dictionary::addCity(SearchNode City) {
    loadFactorCheck();
    // get index
    int index = linearProbeIndex(City.getCityName(), hashIndex(City.getCityName()));
    table[index] = City; // add city
    numCities++;
}

/*
 * addNeighbor()
 * Parameters: two cities and distance between them
 * Purpose: add neighbor to city
 * Returns: none
 */
void Dictionary::addNeighbor(string city1, string city2, double distance) {
    // get indexes for city1 and city 2
    int index1 = linearProbeIndex(city1, hashIndex(city1)); 
    int index2 = linearProbeIndex(city2, hashIndex(city2));
    table[index1].addNeighbor(city2, distance); // add neighbor to city1
    table[index2].addNeighbor(city1, distance); // add neighbor to city2
}
/** *****************************************************************\
*                   hashtable maintaining functions                  *
\********************************************************************/
/* expand()
 * parameters: none
 * purpose: expands the capacity and rehashes all cities
 * returns: n/a
 */
void Dictionary::expand()
{
    int        oldCapacity = capacity;
    SearchNode *oldTable    = table; // save old table to delete it

    capacity = 2 * capacity + 2;        // update capacity
    table    = new SearchNode[capacity]; // create new table
    SearchNode s;
    for (int i = 0; i < capacity; i++) {
        table[i] = s;
    }
    for (int i = 0; i < oldCapacity; i++) {
        if (oldTable[i].getCityName() != "NULL") { // if keywrd empty: continue,
            SearchNode curr = oldTable[i]; // else, make copy of word entry,
            string    key  = curr.getCityName(); // & put into new table

            // linear probe index uses new table
            table[linearProbeIndex(key, hashIndex(key))] = curr;
        }
    }
    delete [] oldTable;
}

/* loadFactorCheck()
 * parameters: none
 * purpose: checks the load factor and rehashes if necessary
 * returns: n/a
 */
void Dictionary::loadFactorCheck()
{
    double c  = capacity * 1.0;
    double nc = numCities * 1.0;
    if (nc / c > .7) {
        expand();
    }
} 

/** *****************************************************************\
*                           hash functions                           *
\********************************************************************/

/* linearProbeIndex()
 * parameters:
 *  -   int index represents the original hash index for a key
 *  -   string &key is a key to find the index for
 * purpose: to find the correct index for a key using linear probing
 * returns: an integer representing the key's index
 */
int Dictionary::linearProbeIndex(string key, int index)
{
    int  attempt = 0;
    bool found   = false;
    while (!found) {
        index = (index + attempt) % capacity;
        if (table[index].getCityName() == "NULL") { 
            return index;
        } else if (table[index].getCityName() == key) {
            return index;
        }
        attempt++;
    }
    return 0;
}

/* hashIndex()
 * parameters:
 *  -   string &key is a key to find an index for
 * purpose: calls the hash function on the key, then mods it to get an
 *          index
 * returns: the index corresponding to the key
 */
int Dictionary::hashIndex(string key)
{
    // first get hash value for key
    // then mod by capacity to get index
    return (hash<string>{}(key) % capacity);
}
