#include "../Headers/graph.hpp"


Graph::Graph(int vertices) : vertices(vertices), adjList(vertices), route(0) {
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

pair<vector<int>, vector<string>> Graph::simulateContinuousCarJourney(int start, int destination) {
    vector<int> parent(vertices, -1); 
    vector<int> times = dijkstra(start, parent);
    vector<string> path;
    
    vector<int> route;
    vector<int> route1;

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

                route1.push_back(current);

                string r = "Node " + to_string(prevNode) + " --> Node "+ to_string(current) + " (" + to_string(travelTime) + 
                            " mins, " + to_string(totalDistance) + " km)\n";
                path.push_back(r);

               
                break;
            }
        }
        current = prevNode;
    }

    route1.push_back(start);
    reverse(route1.begin(), route1.end());

    cout << "\nTotal Time: " << totalTime << " mins\n";
    cout << "Total Distance: " << totalDistance << " km\n";
    cout << "Journey completed!\n";

    return {route1, path};
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

void Graph::saveAdjacencyListToFile(const string& filename) {
    json adjListJson;

    for (int i = 0; i < adjList.size(); ++i) {
        for (const auto& edge : adjList[i]) {
            adjListJson[std::to_string(i)].push_back({{"neighbor", edge.first}, {"distance", edge.second.first}, {"time", edge.second.second}});
        }
    }
    
    ofstream file(filename);
    file << adjListJson.dump(4); 
    file.close();
}

void Graph:: saveRouteToJson(const vector<int>& route, const string& filename) {
    json routeJson;
    routeJson["route"] = route;

    ofstream file(filename);
    if (file.is_open()) {
        file << routeJson.dump(4); 
        file.close();
    } else {
        cerr << "Failed to open file " << filename << std::endl;
    }
}

vector<int> Graph::getRoute(){
    return route;
}
