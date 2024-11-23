#ifndef GRAPH_H
#define GRAPH_H

#include "../../util/libs.cpp"

class Graph {
private:
    int vertices;  // Number of intersections
    vector<vector<pair<int, pair<int, int>>>> adjList; // (neighbor, (distance, time))

public:
    // Constructor
    Graph(int vertices);

    // Add an edge
    void addEdge(int u, int v, int distance, int time);

    // Dijkstra's algorithm based on time
    vector<int> dijkstra(int start, vector<int>& parent);

    // Simulate a continuous car journey
    void simulateContinuousCarJourney(int start, int destination);

    // Display the graph
    void displayGraph() const;

    // Method to save adjacency list to a JSON file
    void saveAdjacencyListToFile(const std::string& filename);
};

#endif // GRAPH_H
