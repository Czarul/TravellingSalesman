#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include "graph.h"
#include "bfs.h"
#include "ucs.h"
#include "aStar.h"

using namespace std;

ofstream out("afisare.out");

struct edge {
    int src, dest, cost;
};

int main() {
    int numNodes;
    cout << "Enter the number of nodes: ";
    cin >> numNodes;

    // Generate the complete graph
    vector<list<pair<int, int>>> adjList = generateCompleteAdjacencyList(numNodes);
    //vector<list<pair<int, int>>> adjList = readGraphFromFile("citire.in");
    vector<vector<int>> distances = convertToAdjacencyMatrix(adjList);

    // Print the generated graph
    out << "Generated complete graph with random weights:" << endl;
    printAdjacencyList(adjList, out);

    // Print the adjacency matrix
    out << "\nGraph in Adjacency Matrix format:" << endl;
    printAdjacencyMatrix(distances, out);

    // BFS Solution
    out << "\n-----------------------------BFS SOLUTION-----------------------------\n";
    solveBFS(adjList, distances, numNodes, out);

    // UCS Solution
    out << "\n\n-----------------------------UCS SOLUTION-----------------------------\n";
    solveUCS(adjList, numNodes, out);

    // AStar Solution
    out << "\n\n-----------------------------AStar SOLUTION-----------------------------\n";
    solveAStar(adjList,distances, numNodes, out);

    return 0;
}
