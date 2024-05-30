#include "ucs.h"
#include "graph.h"
#include <queue>
#include <vector>
#include <algorithm>

struct State {
    int node;
    int cost;
    vector<int> path;

    State(int n, int c, const vector<int>& p) : node(n), cost(c), path(p) {}

    bool operator<(const State& other) const {
        return cost > other.cost;
    }
};

vector<int> solveTSP_UCS(const vector<list<pair<int, int>>>& graph, int numNodes) {
    priority_queue<State> pq;
    pq.push(State(0, 0, { 0 }));
    vector<int> bestPath;

    while (!pq.empty()) {
        State currentState = pq.top();
        pq.pop();

        int currentNode = currentState.node;
        int currentCost = currentState.cost;
        vector<int> currentPath = currentState.path;

        if (currentPath.size() == numNodes) {
            if (bestPath.empty() || calculatePathCost(graph, bestPath) > calculatePathCost(graph, currentPath)) {
                bestPath = currentPath;
            }
            continue;
        }

        for (const auto& neighbor : graph[currentNode]) {
            int nextNode = neighbor.first;
            int edgeCost = neighbor.second;
            int newCost = currentCost + edgeCost;

            if (find(currentPath.begin(), currentPath.end(), nextNode) == currentPath.end()) {
                vector<int> newPath = currentPath;
                newPath.push_back(nextNode);
                pq.push(State(nextNode, newCost, newPath));
            }
        }
    }

    return bestPath;
}

void solveUCS(const vector<list<pair<int, int>>>& adjList, int numNodes, ofstream& out) {
    vector<int> bestPath = solveTSP_UCS(adjList, numNodes);
    bestPath.push_back(0);

    if (!bestPath.empty()) {
        out << "\nThe best path, with a cost of " << calculatePathCost(adjList, bestPath) << " is:\n";
        for (int node : bestPath) {
            out << node << " ";
        }
    }
    else {
        out << "\nNo valid path found!" << endl;
    }
}
