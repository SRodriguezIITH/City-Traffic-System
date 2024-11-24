#ifndef GRAPH_H
#define GRAPH_H

#include "../../util/libs.cpp"

class Graph {
private:
    int vertices;  // Number of intersections
    vector<vector<pair<int, pair<int, int>>>> adjList; // (neighbor, (distance, time))
    vector<int> route; // Stores the current journey route

    friend class Report;

public:
    // Constructor
    Graph(int vertices);

    // Add an edge 
    void addEdge(int u, int v, int distance, int time);

    // Dijkstra's algorithm to find shortest path based on time and distance
    vector<double> dijkstra(int start, vector<int>& parent);

    // Simulate a continuous car journey
    pair<vector<int>, vector<string>> simulateContinuousCarJourney(int start, int destination);

    // Display the graph structure
    void displayGraph() const;

    // Save the adjacency list to a JSON 
    void saveAdjacencyListToFile(const string& filename);

    // Save optimal route to a JSON 
    void saveRouteToJson(const vector<int>& route, const string& filename);

    vector<int> getRoute();
};

#endif // GRAPH_H
