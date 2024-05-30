#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>
#include <utility>
#include <fstream>
#include <string>

using namespace std;

vector<list<pair<int, int>>> generateCompleteAdjacencyList(int numNodes);
vector<vector<int>> convertToAdjacencyMatrix(const vector<list<pair<int, int>>>& graph);
vector<list<pair<int, int>>> readGraphFromFile(const string& filename);
void printAdjacencyList(const vector<list<pair<int, int>>>& adjacencyList, ofstream& out);
void printAdjacencyMatrix(const vector<vector<int>>& matrix, ofstream& out);
int calculatePathCost(const vector<list<pair<int, int>>>& graph, const vector<int>& path);

#endif // GRAPH_H
