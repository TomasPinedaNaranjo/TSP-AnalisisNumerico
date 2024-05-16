import networkx as nx
import random
import matplotlib.pyplot as plt

def generate_complete_graph_with_coordinates(coordenadas_file, weight_range=(1, 100)):
    G = nx.Graph()

    with open(coordenadas_file, 'r') as file:
        for i, line in enumerate(file):
            x, y = map(float, line.strip().split())
            G.add_node(i, pos=(x, y))

    for u in G.nodes():
        for v in G.nodes():
            if u != v:
                distance = random.randint(*weight_range)
                G.add_edge(u, v, weight=distance)

    return G

def plot_graph_step(G, tour, current_node, pos):
    plt.clf()
    nx.draw(G, pos, with_labels=True, node_color='lightblue', node_size=500)
    path_edges = list(zip(tour, tour[1:]))
    nx.draw_networkx_edges(G, pos, edgelist=path_edges, edge_color='red', width=2)
    nx.draw_networkx_nodes(G, pos, nodelist=[current_node], node_color='green', node_size=500)
    edge_labels = nx.get_edge_attributes(G, 'weight')
    nx.draw_networkx_edge_labels(G, pos, edge_labels=edge_labels)
    plt.pause(0.5)

def calculate_tour_cost(G, tour):
    return sum(G[tour[i]][tour[i+1]]['weight'] for i in range(len(tour)-1))

def nearest_neighbor_tsp_with_distances(G, start_node=None, distancias_file=None):
    if start_node is None:
        start_node = random.choice(list(G.nodes))

    if distancias_file is not None:
        with open(distancias_file, 'r') as file:
            for i, line in enumerate(file):
                distances = map(int, line.strip().split())
                for j, distance in enumerate(distances):
                    if j in G:
                        G[start_node][j]['weight'] = distance
                    else:
                        print(f"Advertencia: Nodo {j} en la línea {i + 1} no existe en el grafo.")

    pos = nx.get_node_attributes(G, 'pos')
    plt.ion()
    plt.show()
    unvisited = set(G.nodes)
    unvisited.remove(start_node)
    tour = [start_node]
    current_node = start_node

    plot_graph_step(G, tour, current_node, pos)

    while unvisited:
        next_node = min(unvisited, key=lambda node: G[current_node][node]['weight'])
        unvisited.remove(next_node)
        tour.append(next_node)
        current_node = next_node
        plot_graph_step(G, tour, current_node, pos)

    tour.append(start_node)
    plot_graph_step(G, tour, current_node, pos)

    print(tour)
    tour_cost = calculate_tour_cost(G, tour)
    print(f'cost:{tour_cost}')

    plt.ioff()
    plt.show()

if __name__ == '__main__':
    G = generate_complete_graph_with_coordinates('coordenadas1.txt')
    nearest_neighbor_tsp_with_distances(G, start_node=0, distancias_file='distancias1.txt')

