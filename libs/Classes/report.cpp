#include "../Headers/report.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>

Report::Report(const Graph& graph, double distanceWeight, double timeWeight)
    : graph(graph), distanceWeight(distanceWeight), timeWeight(timeWeight) {}

string Report::classifyRoad(double cost) {
    if (cost < criteria1) return "Low traffic";
    if (cost < criteria2 && cost > criteria1) return "Moderate traffic";
    else return "High traffic";
}

void Report::saveTextReport(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << "\n";
        return;
    }

    for (int i = 0; i < graph.vertices; ++i) {
        for (const auto& neighbor : graph.adjList[i]) {
            int neighborNode = neighbor.first;
            int distance = neighbor.second.first;
            int time = neighbor.second.second;
            double cost = distanceWeight * distance + timeWeight * time;

            string remark = classifyRoad(cost);

            file << "Road " << i << " -> " << neighborNode
                 << ": " << remark
                 << " ("
                 << "Time: " << time << " mins, Distance: " << distance << " km)\n";
        }
    }

    file.close();
    cout << "-> Traffic Report Generated\n";
}
