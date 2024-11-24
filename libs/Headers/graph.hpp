#ifndef GRAPH_H
#define GRAPH_H

#include "../../util/libs.cpp"

class Graph {
private:
    int vertices;  // Number of intersections
    vector<vector<pair<int, pair<int, int>>>> adjList; // (neighbor, (distance, time))
    vector<int> route; // Stores the current journey route

public:
    // Constructor
    Graph(int vertices);

    // Add an edge between nodes u and v with given distance and time
    void addEdge(int u, int v, int distance, int time);

    // Dijkstra's algorithm to find shortest path based on time
    vector<int> dijkstra(int start, vector<int>& parent);

    // Simulate a continuous car journey from start to destination
    pair<vector<int>, vector<string>> simulateContinuousCarJourney(int start, int destination);

    // Display the graph structure (distance and time between nodes)
    void displayGraph() const;

    // Save the adjacency list to a JSON file for external use
    void saveAdjacencyListToFile(const string& filename);

    // Save the simulated route to a JSON file
    void saveRouteToJson(const vector<int>& route, const string& filename);

    // Getter for the journey route
    vector<int> getRoute();
};

#endif // GRAPH_H
