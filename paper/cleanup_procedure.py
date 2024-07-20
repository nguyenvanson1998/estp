from utilities.tree import Tree
from utilities.point import fermat_point
from utilities.prim import MST

from proposed.local_optimization import local_optimization


def exists_steiner_degree_under_3(T: Tree, S: list):
    for s in S:
        if T.degree(s) < 3:
            return True
    return False


def exists_steiner_edge(T: Tree):
    for edge in T.edge_list:
        if edge[0].steiner and edge[1].steiner:
            return True
    return False


def cleanup(T: Tree, X: list, S: list):
    """
    Thuật toán 2: Thủ tục dọn dẹp
    - Loại bỏ các điểm Steiner bậc dưới 3 khỏi T
    """

    T_ = T.copy()
    S_ = S.copy()

    while exists_steiner_degree_under_3(T_, S_):
        removed_nodes = []
        for s in S_:
            if T_.degree(s) == 1:
                T_.remove_node(s)
                removed_nodes.append(s)
            elif T_.degree(s) == 2:
                x, y = T_.adjacency_list[s]
                T_.remove_node(s)
                T_.add_edge(x, y)
                removed_nodes.append(s)

        temp_S = []
        length = len(removed_nodes)
        it = 0
        for s in S_:
            if it < length and s is removed_nodes[it]:
                it += 1
            else:
                temp_S.append(s)
        S_ = temp_S
        
        for s in S_:
            if T_.degree(s) == 3:
                s.set_axes(fermat_point(T_.adjacency_list[s]))

        T_ = MST(X + S_)

    if exists_steiner_edge(T_):
        S_ = local_optimization(T_, S_)

    return T_, S_

