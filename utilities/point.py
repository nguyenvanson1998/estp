import numpy as np
import math


class Point:
    """
    Mỗi điểm trong không gian R^d có các thông tin:
    - axes: Vector tọa độ d chiều (dùng cấu trúc mảng của NumPy)
    - steiner: Biến nhị phân, cho biết đây là điểm Steiner hay terminal
    VD: Điểm terminal A(1.0, 2.0, 3.0) có:
    - axes = np.array([1.0, 2.0, 3.0])
    - steiner = False
    """

    def __init__(self, axes=None, steiner=False):
        self.axes = axes
        self.steiner = steiner

    def __hash__(self):
        return hash(id(self))

    def equals(self, p):
        return np.array_equal(self.axes, p.axes)

    @classmethod
    def from_line(cls, line: str):
        axes = [float(axis) for axis in line.split()]
        return cls(np.array(axes))

    def set_axes(self, axes):
        self.axes = axes


# Tính khoảng cách euclidean giữa 2 điểm
def distance(A, B):
    return np.linalg.norm(A.axes - B.axes)


# Tính tích vô hướng 2 vector BA và BC
def dot_product(A, B, C):
    return np.dot(A.axes - B.axes, C.axes - B.axes)


# Tính góc giữa 2 vector BA và BC theo độ đo radiant
def angle(A, B, C):
    if np.array_equal(A.axes, B.axes) or np.array_equal(A.axes, C.axes) or np.array_equal(C.axes, B.axes):
        return math.pi
    norm_BA = (B.axes - A.axes) / np.linalg.norm(B.axes - A.axes)
    norm_BC = (B.axes - C.axes) / np.linalg.norm(B.axes - C.axes)
    return np.arccos(np.clip(np.dot(norm_BA, norm_BC), -1, 1))


# Tính trọng tâm của 1 tập điểm
def center_of_gravity(points: list):
    point_axes = [p.axes for p in points]
    return np.sum(point_axes, axis=0) / len(points)


# Tính điểm Fermat của tam giác
def fermat_point(points):
    if len(points) != 3:
        return None

    A, B, C = points

    # Kiểm tra 1 trong 3 góc > 120 độ, trùng điểm Fermat
    angle_A = angle(B, A, C)
    if angle_A >= math.pi * 2 / 3:
        return A.axes
    angle_B = angle(A, B, C)
    if angle_B >= math.pi * 2 / 3:
        return B.axes
    angle_C = angle(A, C, B)
    if angle_C >= math.pi * 2 / 3:
        return C.axes

    # Tính điểm Fermat theo công thức vector
    a = distance(B, C)
    b = distance(A, C)
    c = distance(A, B)

    x = 1 / math.sin(angle_A + math.pi / 3)
    y = 1 / math.sin(angle_B + math.pi / 3)
    z = 1 / math.sin(angle_C + math.pi / 3)

    _D = a*x+b*y+c*z

    return (a*x/_D) * A.axes + (b*y/_D) * B.axes + (c*z/_D) * C.axes


# if __name__ == '__main__':
#     A = Point(np.array([1.0, 3.0, 1.0, 2.0]))
#     B = Point(np.array([2.0, 3.0, 2.0, 2.0]))
#     C = Point(np.array([1.0, 3.0, 2.0, 2.0]))
#     F = Point(fermat_point([A, B, C]))
#     print(F.axes)
#     ab = distance(A, B)
#     bc = distance(B, C)
#     ca = distance(C, A)
#
#     print(distance(F, A) + distance(F, B) + distance(F, C))
#     print(ab + bc)
#     print(bc + ca)
#     print(ab + ca)
