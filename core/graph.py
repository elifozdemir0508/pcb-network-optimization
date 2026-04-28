class Graph:
    """
    PCB bağlantı ağını temsil eden temel graph sınıfı.

    Node: PCB üzerindeki bağlantı noktası
    Edge: İki bağlantı noktası arasındaki bağlantı
    Weight: Bağlantı maliyeti / mesafe / ağırlık
    """

    def __init__(self):
        self.adjacency_list = {}

    def add_node(self, node):
        """Graph'a yeni bir node ekler."""
        if node not in self.adjacency_list:
            self.adjacency_list[node] = []

    def add_edge(self, source, target, weight=1):
        """
        İki node arasında ağırlıklı bağlantı oluşturur.
        PCB ağı yönsüz kabul edildiği için bağlantı iki tarafa da eklenir.
        """
        self.add_node(source)
        self.add_node(target)

        self.adjacency_list[source].append((target, weight))
        self.adjacency_list[target].append((source, weight))

    def get_nodes(self):
        """Graph içindeki tüm node'ları döndürür."""
        return list(self.adjacency_list.keys())

    def get_neighbors(self, node):
        """Belirli bir node'un komşularını döndürür."""
        return self.adjacency_list.get(node, [])

    def get_edges(self):
        """Graph içindeki tüm edge'leri tekrar etmeden döndürür."""
        edges = []
        visited = set()

        for source in self.adjacency_list:
            for target, weight in self.adjacency_list[source]:
                edge_key = tuple(sorted((source, target)))

                if edge_key not in visited:
                    edges.append((source, target, weight))
                    visited.add(edge_key)

        return edges

    def display_graph(self):
        """Graph yapısını ekrana yazdırır."""
        for node, neighbors in self.adjacency_list.items():
            print(f"{node} -> {neighbors}")


if __name__ == "__main__":
    graph = Graph()

    graph.add_edge("A", "B", 4)
    graph.add_edge("A", "C", 2)
    graph.add_edge("B", "D", 5)
    graph.add_edge("C", "D", 1)

    graph.display_graph()

    print("Nodes:", graph.get_nodes())
    print("Edges:", graph.get_edges())
