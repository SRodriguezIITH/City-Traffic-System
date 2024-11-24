#include "./genCityTraffic.cpp"
#include "../../util/constants.cpp"

void Simulate() {
    Graph cityGraph = generateCityTraffic(nodes, maxDistance, maxTime);


    cityGraph.saveAdjacencyListToFile("../../dataset/city.json");
    printTraffic(cityGraph);

    cout << "\nSimulating Car Journey:\n";
    int s,d;

    while(cout<<"Enter source destination: ", cin>>s>>d){
        cityGraph.simulateContinuousCarJourney(s, d);
    }
    return;
}