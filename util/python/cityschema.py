import json
import networkx as nx
import matplotlib.pyplot as plt

def load_adjacency_list(filename):
    """
    Load adjacency list from a JSON file.
    """
    with open(filename, 'r') as file:
        adj_list = json.load(file)
    return adj_list

def convert_to_networkx(adj_list):
    """
    Convert adjacency list to a NetworkX graph.
    """
    G = nx.DiGraph()
    for node, edges in adj_list.items():
        for edge in edges:
            neighbor = edge["neighbor"]
            distance = edge["distance"]
            time = edge["time"]
            G.add_edge(int(node), neighbor, distance=distance, time=time)
    return G

def visualize_graph(G):
    """
    Visualize the graph using NetworkX and Matplotlib.
    """
    pos = nx.spring_layout(G)
    nx.draw(G, pos, with_labels=True, node_color="lightblue", node_size=500, font_weight="bold")

    edge_labels = {
        (u, v): f"{data['distance']} km, {data['time']} min"
        for u, v, data in G.edges(data=True)
    }
    nx.draw_networkx_edge_labels(G, pos, edge_labels=edge_labels, font_size=8)

    plt.title("City Traffic Graph")
    plt.show()

# Load the adjacency list from the JSON file
filename = "../../dataset/city.json"
adj_list = load_adjacency_list(filename)

# Convert to NetworkX graph and visualize
G = convert_to_networkx(adj_list)
visualize_graph(G)
