#ifndef ASTAR_H
#define ASTAR_H

#include <vector>
#include <list>
#include <utility>
#include <fstream>

using namespace std;

void solveAStar(const vector<list<pair<int, int>>>& adjList, const vector<vector<int>>& distances, int numNodes, ofstream& out);

#endif // ASTAR_H
