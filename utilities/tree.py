from utilities import point


class Tree:
    """
    Cây được biểu diễn bởi ma trận kề:
    - adjacency_list: Ma trận kề - sử dụng dictionary của list
    """

    def __init__(self):
        self.adjacency_list = {}

    @classmethod
    def from_nodes(cls, nodes: list):
        new_tree = cls()
        for node in nodes:
            new_tree.adjacency_list[node] = []
        return new_tree

    def copy(self):
        new_tree = Tree()
        for node, adjacency in self.adjacency_list.items():
            new_tree.adjacency_list[node] = adjacency.copy()
        return new_tree

    def degree(self, node):
        return len(self.adjacency_list[node])

    def add_node(self, node):
        if node not in self.adjacency_list:
            self.adjacency_list[node] = []

    def remove_node(self, node):
        for connected_node in self.adjacency_list[node]:
            self.adjacency_list[connected_node].remove(node)
        self.adjacency_list.pop(node)

    def add_edge(self, node_1, node_2):
        self.adjacency_list[node_1].append(node_2)
        self.adjacency_list[node_2].append(node_1)

    def remove_edge(self, node_1, node_2):
        try:
            self.adjacency_list[node_1].remove(node_2)
            self.adjacency_list[node_2].remove(node_1)
        except ValueError:
            pass

    @property
    def edge_list(self):
        edges = []
        for node_1, adjacency in self.adjacency_list.items():
            for node_2 in adjacency:
                if id(node_1) < id(node_2):
                    edges.append((node_1, node_2))
        return edges

    @property
    def l(self):
        edges = self.edge_list
        length = 0.0
        # for p in self.adjacency_list.keys():
        #     print(p.axes)
        for edge in edges:
            length += point.distance(edge[0], edge[1])
        return length
