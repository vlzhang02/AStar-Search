/* 
 * main.cpp
 * By: Valerie Zhang, June 2022
 *
 * Purpose: Runs A* search
 *
 */

#include "SearchNode.h"
#include "AStarSearch.h"
#include <iostream>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Usage: ./astar_search filename \n";
        exit(EXIT_FAILURE);
    }
    AStarSearch a(argv[1]);
    a.run();
    
    return 0;
}