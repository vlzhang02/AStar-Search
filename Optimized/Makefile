###
### Makefile for astar_search"
###
### Author: Valerie Zhang
###

CXX      = clang++
CXXFLAGS = -g3 -Ofast -Wall -Wextra -std=c++11 

astar_search: main.o AStarSearch.o Dictionary.o SearchNode.o
	$(CXX) $(CXXFLAGS) -o $@ $^

AStarSearch.o: AStarSearch.cpp
	$(CXX) $(CXXFLAGS) -c $^

Dictionary.o: Dictionary.cpp
	$(CXX) $(CXXFLAGS) -c $^

SearchNode.o: SearchNode.cpp
	$(CXX) $(CXXFLAGS) -c $^

unit_test: unit_test_driver.o SearchNode.o Dictionary.o
	$(CXX) $(CXXFLAGS) $^

clean: 
	rm *.o a.out *~ *#