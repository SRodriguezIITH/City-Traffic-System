import json
import networkx as nx
import matplotlib.pyplot as plt

def load_adjacency_list(filename):
    try:
        with open(filename, 'r') as file:
            adj_list = json.load(file)
        return adj_list
    except FileNotFoundError:
        print(f"Error: File {filename} not found.")
        return {}
    except json.JSONDecodeError:
        print(f"Error: File {filename} is not a valid JSON.")
        return {}

def load_route(filename):
    try:
        with open(filename, 'r') as file:
            route_data = json.load(file)
        return route_data.get("route", [])
    except FileNotFoundError:
        print(f"Error: File {filename} not found.")
        return []
    except json.JSONDecodeError:
        print(f"Error: File {filename} is not a valid JSON.")
        return []

def convert_to_directed_networkx(adj_list):
    G = nx.DiGraph()
    for node, edges in adj_list.items():
        for edge in edges:
            neighbor = edge["neighbor"]
            distance = edge["distance"]
            time = edge["time"]
            G.add_edge(int(node), int(neighbor), distance=distance, time=time)
    return G

def visualize_directed_graph_with_weights(G, route, city_filename, route_filename):
    pos = nx.spring_layout(G)
    nx.draw(
        G,
        pos,
        with_labels=True,
        node_color="lightblue",
        node_size=700,
        font_weight="bold",
        arrows=True,
        arrowsize=20,
        edgecolors="black",
        arrowstyle="-|>",
        connectionstyle="arc3,rad=0.2"
    )
    edge_labels = {}
    for u, v, data in G.edges(data=True):
        edge_labels[(u, v)] = f"{data['distance']} km\n{data['time']} min"
    nx.draw_networkx_edge_labels(G, pos, edge_labels=edge_labels, font_size=8, label_pos=0.3)

    for u, v, data in G.edges(data=True):
        nx.draw_networkx_edges(
            G,
            pos,
            edgelist=[(u, v)],
            width=2,
            edge_color="lightgray",
            style="dotted",
            alpha=0.6,
            connectionstyle="arc3,rad=0.2",
        )
    plt.savefig(city_filename)

    if route:
        route_edges = [(route[i], route[i + 1]) for i in range(len(route) - 1)]
        for u, v in route_edges:
            data = G[u][v]
            nx.draw_networkx_edges(
                G,
                pos,
                edgelist=[(u, v)],
                edge_color="red",
                width=3,
                arrows=True,
                arrowsize=25,
                connectionstyle="arc3,rad=0.2",
            )
            nx.draw_networkx_edge_labels(
                G,
                pos,
                edge_labels={(u, v): f"{data['distance']} km\n{data['time']} min"},
                font_size=8,
                font_color="red",
                label_pos=0.5
            )

    plt.title("City Traffic Graph with Weights and Arc Style")
    
    plt.savefig(route_filename)
    plt.show()

adjacency_list_file = "../../dataset/city.json"
route_file = "../../dataset/route.json"
city_image = "../../dataset/cityscheme.png"
route_image = "../../dataset/routeplan.png"

adj_list = load_adjacency_list(adjacency_list_file)
route = load_route(route_file)

if adj_list:
    G = convert_to_directed_networkx(adj_list)
    visualize_directed_graph_with_weights(G, route, city_filename=city_image, route_filename=route_image)
else:
    print("Graph visualization failed due to invalid input data.")
