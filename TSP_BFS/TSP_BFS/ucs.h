#ifndef UCS_H
#define UCS_H

#include <vector>
#include <list>
#include <utility>
#include <fstream>

using namespace std;

void solveUCS(const vector<list<pair<int, int>>>& adjList, int numNodes, ofstream& out);

#endif // UCS_H
