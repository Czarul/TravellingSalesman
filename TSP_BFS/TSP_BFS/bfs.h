#ifndef BFS_H
#define BFS_H

#include <vector>
#include <list>
#include <utility>
#include <fstream>

using namespace std;

void solveBFS(const vector<list<pair<int, int>>>& adjList, const vector<vector<int>>& distances, int numNodes, ofstream& out);

#endif // BFS_H
