#ifndef REPORT_HPP
#define REPORT_HPP

#include "../../util/constants.cpp"
#include "graph.hpp"

class Report {
private:
    const Graph& graph;
    double distanceWeight;
    double timeWeight;

    std::string classifyRoad(double cost);

public:
    Report(const Graph& graph, double distanceWeight = alpha, double timeWeight = beta);

    void saveTextReport(const std::string& filename);
};

#endif
