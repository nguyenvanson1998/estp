import random
import sys
import numpy as np


class Point:
    def __init__(self, d: int):
        self.axes = np.empty(d, float)
        for i in range(d):
            self.axes[i] = round(random.random(), 2)

    def __eq__(self, other):
        return np.array_equal(self.axes, other.axes)

    def tostring(self):
        return ' '.join([str('{:.2f}'.format(self.axes[i])).lstrip('0') for i in range(self.axes.size)])


def random_test(d: int, n: int, cnt: int):
    with open('data/estein10_%dD.txt' % d, 'w') as out:
        out.write(str(cnt) + '\n')
        points = []

        for _ in range(cnt):
            points.clear()
            out.write(str(n) + '\n')
            for _ in range(n):
                p = Point(d)
                while p in points:
                    p = Point(d)
                points.append(p)

            for p in points:
                out.write(p.tostring() + '\n')


if __name__ == '__main__':
    random_test(3, 10, 10)
    random_test(4, 10, 5)
    random_test(5, 10, 5)

