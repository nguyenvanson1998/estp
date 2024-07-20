import numpy as np

from utilities.point import Point, distance, center_of_gravity


def weiszfeld(geo_median: Point, points: list):
    """
    Thuật toán 5: Thuật toán Weiszfeld
    - Heuristic nhằm tìm ra điểm có tổng khoảng cách tới tập điểm đã cho nhỏ nhất
    """

    total_distance = sum([distance(geo_median, p) for p in points])
    new_center = Point(center_of_gravity(points))

    while True:
        for p in points:
            if geo_median.equals(p):
                return p

        new_center.axes = np.add.reduce([p.axes / distance(p, geo_median) for p in points]) \
                          / sum([1 / distance(p, geo_median) for p in points])
        new_total = sum([distance(new_center, p) for p in points])

        if total_distance <= new_total + 1e-9:
            return geo_median

        geo_median = new_center
        total_distance = new_total