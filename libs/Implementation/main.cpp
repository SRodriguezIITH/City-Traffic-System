#include "../Classes/graph.cpp"

using namespace std;

Graph generateCityTraffic(int nodes, int maxDistance, int maxTime) {
    Graph cityGraph(nodes);

    // Add edges (roads) to the graph
    for (int i = 0; i < nodes; ++i) {
        int roads = rand() % 3 + 1; // Random number of roads
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

// Function to display the traffic details
void printTraffic(const Graph& cityGraph) {
    cout << "\nCity Traffic (Adjacency List Representation):\n";
    cityGraph.displayGraph();
}

int main() {
    int nodes = 12;         
    int maxDistance = 20;  
    int maxTime = 90;       
    int startNode = 3;      
    int destinationNode = 8; 

    // Generate a random city traffic graph
    Graph cityGraph = generateCityTraffic(nodes, maxDistance, maxTime);

    cityGraph.saveAdjacencyListToFile("../../dataset/city.json");

    // Print traffic details
    printTraffic(cityGraph);

    // Simulate a continuous car journey
    cout << "\nSimulating Car Journey:\n";
    int s,d;

    while(cin>>s>>d)
    cityGraph.simulateContinuousCarJourney(s, d);

    return 0;
}
