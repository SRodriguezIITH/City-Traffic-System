import json
import networkx as nx
import matplotlib.pyplot as plt

def load_adjacency_list(filename):
    with open(filename, 'r') as file:
        adj_list = json.load(file)
    return adj_list

def load_route(filename):
    with open(filename, 'r') as file:
        route_data = json.load(file)
    return route_data["route"]

def convert_to_networkx(adj_list):
    G = nx.DiGraph()  
    for node, edges in adj_list.items():
        for edge in edges:
            neighbor = edge["neighbor"]
            distance = edge["distance"]
            time = edge["time"]
            G.add_edge(int(node), neighbor, distance=distance, time=time)
    return G

def visualize_graph(G, route):
    pos = nx.spring_layout(G)
    
    nx.draw(
        G, pos, with_labels=True, node_color="lightblue", node_size=500, font_weight="bold", arrows=True
    )

    edge_labels = {
        (u, v): f"{data['distance']} km, {data['time']} min"
        for u, v, data in G.edges(data=True)
    }
    nx.draw_networkx_edge_labels(G, pos, edge_labels=edge_labels, font_size=8)
    plt.title("City Road Plan")
    plt.savefig("../../dataset/cityscheme.png")

    if route:
        route_edges = [(route[i], route[i + 1]) for i in range(len(route) - 1)]
        nx.draw_networkx_edges(
            G, pos, edgelist=route_edges, edge_color="red", width=2.5, arrows=True
        )

    plt.title("City Traffic Graph with Route")
    plt.savefig("../../dataset/routeplan.png")
    plt.show()
    

filename = "../../dataset/city.json"
route_filename = "../../dataset/route.json"

adj_list = load_adjacency_list(filename)
route = load_route(route_filename)

G = convert_to_networkx(adj_list)

visualize_graph(G, route=route)
