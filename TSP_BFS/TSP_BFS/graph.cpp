#include "graph.h"
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <iostream>

vector<list<pair<int, int>>> generateCompleteAdjacencyList(int numNodes) {
    srand(time(nullptr));
    vector<list<pair<int, int>>> adjacencyList(numNodes);

    for (int i = 0; i < numNodes; ++i) {
        for (int j = i + 1; j < numNodes; ++j) {
            int weight = rand() % 100 + 1;
            adjacencyList[i].push_back(make_pair(j, weight));
            adjacencyList[j].push_back(make_pair(i, weight));
        }
    }

    return adjacencyList;
}

vector<vector<int>> convertToAdjacencyMatrix(const vector<list<pair<int, int>>>& graph) {
    int numNodes = graph.size();
    vector<vector<int>> matrix(numNodes, vector<int>(numNodes, 0));

    for (int i = 0; i < numNodes; ++i) {
        for (const auto& edge : graph[i]) {
            matrix[i][edge.first] = edge.second;
        }
    }

    return matrix;
}

vector<list<pair<int, int>>> readGraphFromFile(const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Error: could not open the file for reading." << endl;
        exit(1);
    }

    vector<list<pair<int, int>>> graph;
    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        int node, neighbor, weight;
        if (!(ss >> node >> neighbor >> weight)) {
            cerr << "Error: invalid file format." << endl;
            exit(1);
        }

        if (graph.size() <= max(node, neighbor)) {
            graph.resize(max(node, neighbor) + 1);
        }

        graph[node].push_back(make_pair(neighbor, weight));
        graph[neighbor].push_back(make_pair(node, weight));
    }

    inFile.close();
    return graph;
}

void printAdjacencyList(const vector<list<pair<int, int>>>& adjacencyList, ofstream& out) {
    for (int i = 0; i < adjacencyList.size(); ++i) {
        for (const auto& edge : adjacencyList[i]) {
            if (i < edge.first) {
                out << i << " " << edge.first << " " << edge.second << endl;
            }
        }
    }
}

void printAdjacencyMatrix(const vector<vector<int>>& matrix, ofstream& out) {
    int numNodes = matrix.size();
    for (int i = 0; i < numNodes; ++i) {
        for (int j = 0; j < numNodes; ++j) {
            out << matrix[i][j] << " ";
        }
        out << endl;
    }
}

int calculatePathCost(const vector<list<pair<int, int>>>& graph, const vector<int>& path) {
    int cost = 0;
    int lastNode = path.back();
    for (const auto& edge : graph[lastNode]) {
        if (edge.first == 0) {
            cost += edge.second;
            break;
        }
    }
    for (int i = 0; i < path.size() - 1; ++i) {
        int currentNode = path[i];
        int nextNode = path[i + 1];
        for (const auto& neighbor : graph[currentNode]) {
            if (neighbor.first == nextNode) {
                cost += neighbor.second;
                break;
            }
        }
    }
    return cost;
}
