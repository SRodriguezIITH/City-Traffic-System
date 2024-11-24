#include "../Headers/graph.hpp"
#include "../../util/constants.cpp"

Graph::Graph(int vertices) : vertices(vertices), adjList(vertices), route(0) {
    srand(time(0));
}

void Graph::addEdge(int u, int v, int distance, int time) {
    adjList[u].emplace_back(v, make_pair(distance, time));            
    adjList[v].emplace_back(u, make_pair(distance, rand() % 50 + 1)); 
}

vector<double> Graph::dijkstra(int start, vector<int>& parent) {
    vector<double> costs(vertices, INF); 
    vector<int> times(vertices, INF);   
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<>> pq;

    costs[start] = 0.0;
    times[start] = 0;
    pq.emplace(0.0, start);
    parent[start] = -1;

    while (!pq.empty()) {
        double currCost = pq.top().first; 
        int currNode = pq.top().second;
        pq.pop();

        if (currCost > costs[currNode]) continue;

        for (const auto& neighbor : adjList[currNode]) {
            int nextNode = neighbor.first;
            int distance = neighbor.second.first;
            int travelTime = neighbor.second.second;

            double newCost = currCost + alpha * distance + beta * travelTime;

            
            if (newCost < costs[nextNode]) {
                costs[nextNode] = newCost;
                times[nextNode] = times[currNode] + travelTime;
                parent[nextNode] = currNode;
                pq.emplace(newCost, nextNode);
            }
        }
    }

    return costs;
}



pair<vector<int>, vector<string>> Graph::simulateContinuousCarJourney(int start, int destination) {
    vector<int> parent(vertices, -1); 
    vector<double> times = dijkstra(start, parent);
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

vector<int> Graph::getRoute() {
    return route;
}
