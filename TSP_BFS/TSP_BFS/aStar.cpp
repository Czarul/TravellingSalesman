#include "aStar.h"
#include "graph.h"
#include <queue>
#include <vector>
#include <algorithm>

// A structure to represent an edge
struct Edge {
    int src, dest, weight;
};

// A structure to represent a subset for union-find
struct Subset {
    int parent;
    int rank;
};

// A utility function to find set of an element i
// (uses path compression technique)
int find(vector<Subset>& subsets, int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// A function that does union of two sets of x and y
// (uses union by rank)
void Union(vector<Subset>& subsets, int x, int y) {
    int rootX = find(subsets, x);
    int rootY = find(subsets, y);

    if (subsets[rootX].rank < subsets[rootY].rank)
        subsets[rootX].parent = rootY;
    else if (subsets[rootX].rank > subsets[rootY].rank)
        subsets[rootY].parent = rootX;
    else {
        subsets[rootY].parent = rootX;
        subsets[rootX].rank++;
    }
}

// Compare two edges according to their weights
bool compare(Edge a, Edge b) {
    return a.weight < b.weight;
}

// The main function to construct MST using Kruskal's algorithm
int kruskalMST(vector<Edge>& edges, int V) {
    // Sort all the edges in non-decreasing order of their weight
    sort(edges.begin(), edges.end(), compare);

    // Allocate memory for creating V subsets
    vector<Subset> subsets(V+1000);

    // Create V subsets with single elements
    for (int v = 0; v < V+1000; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    int mstWeight = 0; // Initialize result

    // Number of edges to be taken is equal to V-1
    for (const auto& edge : edges) {
        int x = find(subsets, edge.src);
        int y = find(subsets, edge.dest);

        // If including this edge does not cause a cycle,
        // include it in the result and increment the index
        // of the result for the next edge
        if (x != y) {
            mstWeight += edge.weight;
            Union(subsets, x, y);
        }
    }

    return mstWeight;
}


void solveAStar(const vector<list<pair<int, int>>>& adjList, const vector<vector<int>>& distances, int numNodes, ofstream& out) {
	vector<bool>visited(numNodes, false);
	visited[0] = true;
	vector<int>path;
	path.push_back(0);
    //starting AStar
    while (path.size() < numNodes) {
        visited[path.back()]=true;
        vector<pair<int, int>>nextNode;
        for (int src = 0; src < numNodes; src++) {
            if (visited[src])continue;
            pair<int, int>node = { 0, src };
            vector<Edge>edges;
            for (int i = 0; i < numNodes; i++) {
                for (auto j : adjList[i]) {
                    if (!visited[i] && !visited[j.first] && src != i && src != j.first) {
                        node.first = min(node.first, distances[j.first][0]);
                        Edge edge;
                        edge.src = i;
                        edge.dest = j.first;
                        edge.weight = j.second;
                        edges.push_back(edge);
                    }
                }
            }
            node.first += distances[src][path.back()];
            node.first += kruskalMST(edges, numNodes - path.size() - 1);
            nextNode.push_back(node);
        }
        sort(nextNode.begin(), nextNode.end());
        path.push_back(nextNode[0].second);
        nextNode.clear();
    }
    path.push_back(0);
    if (!path.empty()) {
        out << "\nThe best path, with a cost of " <<calculatePathCost(adjList, path)<< " is:\n";
        for (int node : path) {
            out << node << " ";
        }
    }
    else {
        out << "\nNo valid path found!" << endl;
    }
}