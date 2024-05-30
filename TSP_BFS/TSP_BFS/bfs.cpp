#include "bfs.h"
#include <queue>
#include <algorithm>

vector<pair<int, vector<int>>> paths;

void BFSSolution(int node, int noOfNodesVisited, int noOfNodesToVisit, int cost, vector<int> path,
    vector<list<pair<int, int>>> adjacencyList, vector<bool> visited, vector<vector<int>> distances) {
    visited[node] = true;
    noOfNodesVisited++;
    if (!path.empty())
        cost += distances[node][path.back()];
    path.push_back(node);
    queue<int> nextNodesToVisit;
    for (auto i : adjacencyList[node]) {
        if (visited[i.first] == true && i.first == 0 && noOfNodesVisited == noOfNodesToVisit) {
            cost += distances[0][node];
            path.push_back(0);
            paths.push_back({ cost, path });
            return;
        }
        if (!visited[i.first])
            nextNodesToVisit.push(i.first);
    }
    while (!nextNodesToVisit.empty()) {
        BFSSolution(nextNodesToVisit.front(), noOfNodesVisited, noOfNodesToVisit,
            cost, path, adjacencyList, visited, distances);
        nextNodesToVisit.pop();
    }
}

void solveBFS(const vector<list<pair<int, int>>>& adjList, const vector<vector<int>>& distances, int numNodes, ofstream& out) {
    vector<int> path;
    vector<bool> visited(numNodes, false);
    BFSSolution(0, 0, numNodes, 0, path, adjList, visited, distances);
    sort(paths.begin(), paths.end());
    if (!paths.empty()) {
        out << "\nThe best path, with a cost of " << paths[0].first << " is:\n";
        for (int node : paths[0].second) {
            out << node << " ";
        }
    }
    out << "\n\nThere were a total of " << paths.size() << " paths found, the worst of it having a cost of "
        << paths.back().first;
}
