# City Traffic Management System
Overview
The City Traffic Management System is a simulation tool that models the traffic network of a city. The system utilizes graph theory to represent the city's road network and applies algorithms to optimize and visualize traffic flow. The project provides a detailed visualization of the city's road network, and the most efficient routes are highlighted based on predefined input data.

Key Features:
Graph Representation: The city’s road network is represented as a directed graph where intersections are nodes and roads are edges.
Weighted Edges: Each edge in the graph carries information about the road's distance and travel time.
Route Optimization: The application supports visualizing the shortest or most efficient routes based on input data.
Visualization: The city’s road network is visualized with clear node labels, edge weights, and the highlighted route.
File Structure
bash

```
root
├── dataset/
│   ├── city.json                # Adjacency list for city roads
│   ├── cityscheme.png           # Visualization of the entire city
│   ├── route.json               # Predefined route data
│   └── routeplan.png            # Image of the selected route
├── libs/
│   ├── Classes/
│   │   ├── graph.cpp            # Graph class implementation
│   │   └── report.cpp           # Report generation for traffic analysis
│   ├── Headers/
│   │   ├── graph.hpp            # Header for graph class
│   │   └── report.hpp           # Header for report class
│   ├── Implementation/
│   │   ├── lib/
│   │   │   └── genCityTraffic.cpp  # City traffic generation functions
│   │   └── simulate.cpp         # Simulation logic
│   └── util/
│       ├── json                 # JSON datastructure for c++
│       ├── python               # Python utilities for visualization
|       |   |
|       |   cityschema.py
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
util/python/python visualize_traffic.py

# Dataset
The city.json file contains the road network as an adjacency list, where each node represents an intersection, and edges represent roads between them.
The route.json file contains a predefined route that will be visualized within the network.

Running the Program:

Once the executable is run, the program will simulate the city traffic and output traffic reports.
The routeplan.png or routeplan.html will display the optimized route on the graph.
Visualizing the Graph:

Visualize the city’s road network and highlight the route using the Python-based visualization script.

# How It Works
Data Loading: The system loads the city.json file, which describes the city’s road network, including intersections (nodes) and roads (edges).
Graph Construction: The city data is used to construct a directed graph using C++ (via graph.cpp and graph.hpp).
Route Generation: The predefined route (from route.json) is processed to display the shortest or most efficient path.
Visualization: The Python-based visualize_traffic.py uses NetworkX to visualize the graph and highlight the selected route with edge labels showing the distance and travel time.
Future Improvements
Real-Time Traffic Updates: Incorporate live traffic data to dynamically update routes and road conditions.
Advanced Pathfinding Algorithms: Implement additional pathfinding algorithms like A* or Bellman-Ford for more accurate route recommendations.
Graphical User Interface (GUI): Build a GUI that allows users to manually input routes and interact with the traffic simulation in real-time.