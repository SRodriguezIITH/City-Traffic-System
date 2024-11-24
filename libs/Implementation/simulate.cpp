#include "./genCityTraffic.cpp"
#include "../../util/constants.cpp"
#include "../Classes/report.cpp"

void Simulate() {
    Graph cityGraph = generateCityTraffic();
    Report report = Report(cityGraph, alpha, beta);
    cityGraph.saveAdjacencyListToFile("../../dataset/city.json");
    
    printTraffic(cityGraph);

    cout << "\nSimulating Car Journey:\n";
    int s,d;

    while(cout<<"Enter source destination: ", cin>>s>>d){
        if(s >= nodes || d >= nodes){
            cout<<"Invalid! Intersection Does Not Exist\n\n";
            continue;
        }
        auto simulate = cityGraph.simulateContinuousCarJourney(s, d);
        vector<string> path = simulate.second;
        vector<int> route = simulate.first;

        if(path.empty()){
            cout<<"No Road Exists!\n";
            continue;
        }

        for(int i = path.size() - 1; i >= 0; i--){
            cout<<path[i];
            cout<<endl;
        }
        report.saveTextReport("../../dataset/report.txt");
        cityGraph.saveRouteToJson(route, "../../dataset/route.json");
    }
    return;
}