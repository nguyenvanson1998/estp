import numpy as np

from utilities.tree import Tree
from utilities.point import dot_product, Point

from proposed.local_optimization import local_optimization


def recover(T: Tree, X: list, S: list):
    """
    Thuật toán 4: Khôi phục Steiner topology
    - Có nhiệm vụ khôi phục Steiner topology cho cây T
    - Xử lý các đỉnh bậc cao hơn 3 trong T
    """

    T_ = T.copy()
    S_ = S.copy()

    for x_i in X + S:
        if T.degree(x_i) > 3:
            edge_list_xi = T.adjacency_list[x_i].copy()
            for _ in range(T.degree(x_i) - 3):
                x_k = edge_list_xi[0]
                x_l = edge_list_xi[1]

                length = len(edge_list_xi)
                for k in range(length):
                    x_kk = edge_list_xi[k]
                    for l in range(k+1, length):
                        x_ll = edge_list_xi[l]
                        if dot_product(x_kk, x_i, x_ll) > dot_product(x_k, x_i, x_l):
                            x_k = x_kk
                            x_l = x_ll

                s = Point(np.copy(x_i.axes), steiner=True)
                S_.append(s)

                T_.remove_edge(x_i, x_k)
                T_.remove_edge(x_i, x_l)
                edge_list_xi.remove(x_k)
                edge_list_xi.remove(x_l)

                T_.add_node(s)
                T_.add_edge(x_i, s)
                T_.add_edge(x_k, s)
                T_.add_edge(x_l, s)

    S_ = local_optimization(T_, S_)

    return T_, S_
