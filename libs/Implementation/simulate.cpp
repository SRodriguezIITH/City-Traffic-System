#include "./genCityTraffic.cpp"
#include "../../util/constants.cpp"

void Simulate() {
    Graph cityGraph = generateCityTraffic(nodes, maxDistance, maxTime);
    cityGraph.saveAdjacencyListToFile("../../dataset/city.json");
    
    printTraffic(cityGraph);

    cout << "\nSimulating Car Journey:\n";
    int s,d;

    while(cout<<"Enter source destination: ", cin>>s>>d){
        auto simulate = cityGraph.simulateContinuousCarJourney(s, d);
        vector<string> path = simulate.second;
        vector<int> route = simulate.first;

        for(int i = path.size() - 1; i >= 0; i--){
            cout<<path[i];
            cout<<endl;
        }
        cityGraph.saveRouteToJson(route, "../../dataset/route.json");
    }
    return;
}