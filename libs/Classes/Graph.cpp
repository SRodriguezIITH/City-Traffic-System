#include "../Headers/graph.h"


Graph::Graph(int vertices) : vertices(vertices), adjList(vertices) {
    srand(time(0));
}

void Graph::addEdge(int u, int v, int distance, int time) {
    adjList[u].emplace_back(v, make_pair(distance, time));
    adjList[v].emplace_back(u, make_pair(distance, time)); 
}

vector<int> Graph::dijkstra(int start, vector<int>& parent) {
    vector<int> times(vertices, numeric_limits<int>::max());
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    times[start] = 0;
    pq.emplace(0, start);
    parent[start] = -1; 

    while (!pq.empty()) {
        int currTime = pq.top().first;
        int currNode = pq.top().second;
        pq.pop();

        if (currTime > times[currNode]) continue;

        for (const auto& neighbor : adjList[currNode]) {
            int nextNode = neighbor.first;
            int travelTime = neighbor.second.second; 
            int newTime = currTime + travelTime;

            if (newTime < times[nextNode]) {
                times[nextNode] = newTime;
                parent[nextNode] = currNode; 
                pq.emplace(newTime, nextNode);
            }
        }
    }

    return times;
}

void Graph::simulateContinuousCarJourney(int start, int destination) {
    vector<int> parent(vertices, -1); 
    vector<int> times = dijkstra(start, parent);

    int current = destination;
    cout << "Simulating continuous car journey from Node " << start << " to Node " << destination << ":\n";

    int totalTime = 0;
    int totalDistance = 0;
    while (current != start) {
        int prevNode = parent[current];
        for (const auto& neighbor : adjList[prevNode]) {
            if (neighbor.first == current) {
                int travelTime = neighbor.second.second;  
                int travelDistance = neighbor.second.first; 
                totalTime += travelTime;
                totalDistance += travelDistance;
                cout << "Node " << prevNode << " --> Node " << current
                     << " (" << travelTime << " mins, " << travelDistance << " km)\n";
                break;
            }
        }
        current = prevNode;
    }

    cout << "\nTotal Time: " << totalTime << " mins\n";
    cout << "Total Distance: " << totalDistance << " km\n";
    cout << "Journey completed!\n";
}

void Graph::displayGraph() const {
    for (int i = 0; i < vertices; ++i) {
        cout << "Intersection " << i << ": ";
        for (const auto& neighbor : adjList[i]) {
            cout << "(To: " << neighbor.first
                 << ", Distance: " << neighbor.second.first
                 << ", Time: " << neighbor.second.second << ") ";
        }
        cout << endl;
    }
}


using json = nlohmann::json;

void Graph::saveAdjacencyListToFile(const std::string& filename) {
    json adjListJson;

    for (int i = 0; i < adjList.size(); ++i) {
        for (const auto& edge : adjList[i]) {
            adjListJson[std::to_string(i)].push_back({{"neighbor", edge.first}, {"distance", edge.second.first}, {"time", edge.second.second}});
        }
    }
    
    std::ofstream file(filename);
    file << adjListJson.dump(4); 
    file.close();
}

