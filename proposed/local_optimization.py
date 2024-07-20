from utilities.point import fermat_point
from utilities.tree import Tree

from proposed.weiszfeld import weiszfeld


def local_optimization(T: Tree, S: list):
    """
    Thuật toán 6: Local Optimization
    Tìm kiếm cục bộ nhằm tối ưu vị trí các điểm Steiner với cây đã cho:
    - Giả sử các hàng xóm của điểm không đổi trong quá trình
    - Nếu điểm có 3 hàng xóm, đặt vị trí dlaf điểm Fermat của tam giác
    - Nếu có nhiều hàng xóm, dùng giải thuật Weiszfeld
    - Lặp lại quá trình trên tới khi tổng trọng số không giảm nữa
    """

    length = float('inf')

    while T.l < length - 1e-9:
        length = T.l

        for s in S:
            if T.degree(s) == 3:
                new_s = fermat_point(T.adjacency_list[s])
            else:
                new_s = weiszfeld(s, T.adjacency_list[s]).axes
            s.set_axes(new_s)

    # Loại bỏ các điểm Steiner trùng với hàng xóm
    removed_nodes = []
    for s in S:
        for p in T.adjacency_list[s]:
            if s.equals(p):
                removed_nodes.append(s)
                T.remove_edge(s, p)
                for q in T.adjacency_list[s]:
                    T.add_edge(p, q)
                T.remove_node(s)
                break

    temp_S = []
    length = len(removed_nodes)
    it = 0
    for s in S:
        if it < length and s is removed_nodes[it]:
            it += 1
        else:
            temp_S.append(s)
    return temp_S
