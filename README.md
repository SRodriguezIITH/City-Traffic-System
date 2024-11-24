# City Traffic Management System
Project Submitted by:
Sonit Patil (bm23btech11023)
Ananya Dutpal (bm23btech11007)

## Overview
The City Traffic Management System is a simulation tool that models the traffic network of a city. The system utilizes graph theory to represent the city's road network and applies algorithms to optimize and visualize traffic flow. The project provides a detailed visualization of the city's road network, and the most efficient routes are highlighted based on input source road intersection and destination road intersection.

## Key Features:
Graph Representation: The city’s road network is represented as a bi-directed, bi-weighted graph where intersections are nodes and roads are edges.
Weighted Edges: Each edge in the graph carries information about the road's distance and travel time.
Route Optimization: The application supports visualizing the shortest or most efficient routes based on input data and modified Dijkstra considering both distance and time as a pair for traffic conditions with 40% weightage to distance and 60% weightage to time.
Visualization: The city’s road network is visualized with clear node labels, edge weights, and the highlighted route.

## File Structure:

```
root
├── dataset/
│   ├── city.json                # Adjacency list for city roads
│   ├── cityscheme.png           # Visualization of the entire city as a Graph
│   ├── route.json               # Route Data Saved after Optimization 
│   ├── report.txt               # Traffic Report Created for generated city
│   └── routeplan.png            # Image of the optimal route in city as a Graph
├── libs/
│   ├── Classes/
│   │   ├── graph.cpp            # Graph class implementation
│   │   └── report.cpp           # Report generation for traffic analysis
│   ├── Headers/
│   │   ├── graph.hpp            # Header for graph class
│   │   └── report.hpp           # Header for report class
│   ├── Implementation/
│   │   ├──
│   │   └── genCityTraffic.cpp   # Generates City Nodes and Traffic
│   │   └── main.cpp             # Main CPP file (Run Here)
│   │   └── simulate.cpp         # Simulation logic
│   └── util/
│       ├── json                 # JSON datastructure for c++
│       ├── python               # Python utilities for visualization
│       │   └── cityschema.py    # Visualize city and route (RUN this after main.cpp)
|       |   
│       └── constants.cpp        # Constants used in the application
├── .vscode/
├── README.md                    # Project documentation
└── main.cpp                      # Entry point for traffic simulation
```

## Python Libraries Used:
pip install matplotlib networkx

# Run the following command to simulate city generation and route.
g++ main.cpp -o main.exe or run the main.cpp in libs/Implementation/



# If you need to visualize the city map and routes, you can run the Python script after data files (JSON) are set up.
util/python/python cityschema.py


# Dataset
The city.json file contains the road network as an adjacency list, where each node represents an intersection, and edges represent roads between them.
The route.json file contains a predefined route that will be visualized within the network.
report.txt will give a traffic report of the city

Running the Program:

Once the executable is run, the program will simulate the city traffic and output traffic reports.
The routeplan.png or routeplan.html will display the optimized route on the graph.
Visualizing the Graph:

Visualize the city’s road network and highlight the route using the Python-based visualization script.

# How It Works
1. Data Loading: The system loads the city.json file, which describes the city’s road network, including intersections (nodes) and roads (edges).
2. Graph Construction: The city data is used to construct a directed graph using C++ (via graph.cpp and graph.hpp).
3. Route Generation: A Route is generated though modified Dikjstra and saved in route.json
4. Visualization: The Python-based cityschema.py uses NetworkX to visualize the graph and highlight the selected route with edge labels showing the distance and travel time.

# Future Improvements
1. Real-Time Traffic Updates: Incorporate live traffic data to dynamically update routes and road conditions.
2. Advanced Pathfinding Algorithms: Implement additional pathfinding algorithms like A* or Ball Trees
3. Graphical User Interface (GUI): Build a GUI that allows users to manually input routes and interact with the traffic simulation in real-time.