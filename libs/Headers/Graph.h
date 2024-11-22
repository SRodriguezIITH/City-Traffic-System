#ifndef GRAPH_H
#define GRAPH_H

#include <../../util/libs.cpp>

class Graph {
private:
    int vertices;  // Number of intersections (nodes)
    vector<vector<pair<int, pair<int, int>>>> adjList; // Adjacency list (neighbor, (distance, time))

public:
    // Constructor to initialize the graph with a given number of vertices
    Graph(int vertices);

    // Add an edge between two nodes with distance and time weights
    void addEdge(int u, int v, int distance, int time);

    // Dijkstra's algorithm to find the shortest path based on time
    vector<int> dijkstra(int start, vector<int>& parent);

    // Simulate a continuous car journey from the start node to the destination
    void simulateContinuousCarJourney(int start, int destination);

    // Display the graph (for debugging or visualization)
    void displayGraph() const;
};

#endif // GRAPH_H
