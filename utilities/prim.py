import numpy as np

from utilities.tree import Tree
from utilities.point import distance


def MST(nodes):
    """
    Thuật toán Prim O(n^2) tìm cây khung nhỏ nhất
    """

    n = len(nodes)
    adj_matrix = np.fromfunction(np.vectorize(lambda i, j:
                                 distance(nodes[i], nodes[j])), (n, n), dtype=int)

    parent = np.full(n, -1, dtype=int)
    mst_set = np.zeros(n, dtype=bool)
    node_distance = np.full(n, float('inf'), dtype=float)
    node_distance[0] = 0.0

    for _ in range(n):
        min_index = -1
        min_distance = float('inf')
        for i in range(n):
            if not mst_set[i] and node_distance[i] < min_distance:
                min_distance = node_distance[i]
                min_index = i

        mst_set[min_index] = True

        for i in range(n):
            if not mst_set[i] and adj_matrix[min_index, i] < node_distance[i]:
                node_distance[i] = adj_matrix[min_index, i]
                parent[i] = min_index

    mst = Tree.from_nodes(nodes)
    for i in range(n):
        j = parent[i]
        if j == -1:
            continue
        mst.add_edge(nodes[i], nodes[j])

    return mst


# if __name__ == '__main__':
#     A = Point(np.array([1.0, 1.0]))
#     B = Point(np.array([2.0, 2.0]))
#     C = Point(np.array([1.0, 2.0]))
#     F = Point(fermat_point([A, B, C]))
#     nodes = [A, B, C]
#     print(MST(nodes).l)
#     nodes.append(F)
#     print(MST(nodes).l)
