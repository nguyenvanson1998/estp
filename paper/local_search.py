from scipy.spatial import Delaunay
import numpy as np
from copy import deepcopy
import math

from utilities.point import center_of_gravity, Point
from utilities.prim import MST

from paper.cleanup_procedure import cleanup
from paper.edge_insertion import edge_insertion
from paper.steiner_topology_recovery import recover


def local_search(X: list, _k=3, _l=0.3, _u=0.6, _x=0.0):
    """
    Thuật toán 1: Tìm kiếm cục bộ
    - Tìm cây Steiner T cho tập điểm đầu vào X
    - SỬ dụng phương pháp chèn điểm ngẫu nhiên và lưới tam giác Delaunay
    """

    counter = 1
    S = []
    T = MST(X)

    trial_limit = _k * math.sqrt(len(X))

    while counter <= trial_limit:
        S_ = deepcopy(S)
        point_list = X + S
        point_arr = np.vstack([p.axes for p in point_list])
        DT = Delaunay(point_arr)
        p = _l if _l == _u else np.random.uniform(_l, _u)

        for indexes in DT.simplices:
            simplex = []
            for index in indexes:
                simplex.append(point_list[index])

            s = Point(center_of_gravity(simplex), steiner=True)
            if np.random.random() < p:
                S_.append(s)

        T_ = MST(X + S_)
        T_, S_ = cleanup(T_, X, S_)
        T_, S_ = edge_insertion(T_, X, S_)

        l_T = T.l

        if T_.l - l_T < _x * l_T:
            T_, S_ = recover(T_, X, S_)

        if T_.l - l_T < -1e-9:
            S = S_
            T = T_
            counter = 1
        else:
            counter += 1

    return T, S
