from utilities.point import Point
from utilities.tree import Tree

from paper.local_search import local_search

"""
Chương trình chạy test nhập từ bàn phím cho bài ESTP
Hướng dẫn trong file README.MD
"""

if __name__ == '__main__':
    d = 0
    X = []
    N = int(input())
    for i in range(N):
        axes = input()
        p = Point.from_line(axes)
        if d != 0 and len(p.axes) != d:
            raise ValueError('Number of dimensions doesn\'t match.')
        d = len(p.axes)
        X.append(p)

    T, S = local_search(X)
    print()
    print(T.l)
    print(len(S))
    for p in S:
        print(' '.join([str(a) for a in p.axes]))
