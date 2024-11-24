#include "../Classes/graph.cpp"

Graph generateCityTraffic() {
    Graph cityGraph(nodes);

    for (int i = 0; i < nodes; ++i) {
        int roads = rand() % 3 + 1; 
        for (int j = 0; j < roads; ++j) {
            int neighbor = rand() % nodes;
            if (neighbor != i) {
                int distance = rand() % maxDistance + 1;
                int time = rand() % maxTime + 1;
                cityGraph.addEdge(i, neighbor, distance, time);
            }
        }
    }

    return cityGraph;
}

void printTraffic(const Graph& cityGraph) {
    cout << "\nCity Traffic (Adjacency List Representation):\n";
    cityGraph.displayGraph();
}