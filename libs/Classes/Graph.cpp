#include "../Headers/graph.hpp"

// Constructor
Graph::Graph(int vertices) : vertices(vertices), adjList(vertices), route(0) {
    srand(time(0));
}

// Add an edge between nodes `u` and `v` with same distance but different times
void Graph::addEdge(int u, int v, int distance, int time) {
    adjList[u].emplace_back(v, make_pair(distance, time));            // Forward edge
    adjList[v].emplace_back(u, make_pair(distance, rand() % 50 + 1)); // Backward edge with random time
}

// Dijkstra's algorithm to find shortest path based on time
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

// Simulate a continuous car journey from start to destination
pair<vector<int>, vector<string>> Graph::simulateContinuousCarJourney(int start, int destination) {
    vector<int> parent(vertices, -1); 
    vector<int> times = dijkstra(start, parent);
    vector<string> path;
    vector<int> route;

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

                route.push_back(current);

                string step = "Node " + to_string(prevNode) + " --> Node " + to_string(current) +
                              " (Time: " + to_string(travelTime) + " mins, Distance: " + to_string(travelDistance) + " km)";
                path.push_back(step);

                break;
            }
        }
        current = prevNode;
    }

    route.push_back(start);
    reverse(route.begin(), route.end());

    
    cout << "\nTotal Time: " << totalTime << " mins\n";
    cout << "Total Distance: " << totalDistance << " km\n";

    return {route, path};
}

using json = nlohmann::json;

// Display the graph structure (distance and time between nodes)
void Graph::displayGraph() const{
    for (int i = 0; i < vertices; ++i) {
        cout << "Intersection " << i << ": ";
        for (auto& neighbor : adjList[i]) {
            cout << "(To: " << neighbor.first
                 << ", Distance: " << neighbor.second.first
                 << ", Time: " << neighbor.second.second << ") ";
        }
        cout << endl;
    }
}

// Save the adjacency list to a JSON file
void Graph::saveAdjacencyListToFile(const string& filename) {
    json adjListJson;

    for (int i = 0; i < adjList.size(); ++i) {
        for (const auto& edge : adjList[i]) {
            adjListJson[std::to_string(i)].push_back({
                {"neighbor", edge.first},
                {"distance", edge.second.first},
                {"time", edge.second.second}
            });
        }
    }

    ofstream file(filename);
    if (file.is_open()) {
        file << adjListJson.dump(4);
        file.close();
    } else {
        cerr << "Failed to open file " << filename << endl;
    }
}

// Save the route to a JSON file
void Graph::saveRouteToJson(const vector<int>& route, const string& filename) {
    json routeJson;
    routeJson["route"] = route;

    ofstream file(filename);
    if (file.is_open()) {
        file << routeJson.dump(4);
        file.close();
    } else {
        cerr << "Failed to open file " << filename << endl;
    }
}

// Getter for the current route
vector<int> Graph::getRoute() {
    return route;
}
