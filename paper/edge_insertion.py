import math
import numpy as np

from utilities.tree import Tree
from utilities.point import angle, dot_product, Point

from proposed.local_optimization import local_optimization


def edge_insertion(T: Tree, X: list, S: list):
    """
    Thuật toán 3: Thủ tục chèn cạnh
    - Loại bớt các cặp cạnh kề nhau vi phạm điều kiện góc
    """

    T_ = T.copy()
    S_ = S.copy()

    edges_to_insert = []
    for x_i in X + S:
        for x_j in T_.adjacency_list[x_i]:
            edge_list_xj = [x_l for x_l in T_.adjacency_list[x_j]
                            if not x_l.equals(x_i) and angle(x_i, x_j, x_l) < math.pi * 2 / 3]

            if len(edge_list_xj) > 0:
                x_k = edge_list_xj[0]
                for x_l in edge_list_xj:
                    if dot_product(x_i, x_j, x_l) > dot_product(x_i, x_j, x_k):
                        x_k = x_l
                s = Point(np.copy(x_j.axes), steiner=True)

                S_.append(s)
                T_.remove_edge(x_i, x_j)
                T_.remove_edge(x_j, x_k)

                T_.add_node(s)
                edges_to_insert.append((x_i, s))
                edges_to_insert.append((x_j, s))
                edges_to_insert.append((x_k, s))

    for edge in edges_to_insert:
        T_.add_edge(edge[0], edge[1])

    S_ = local_optimization(T_, S_)

    return T_, S_


