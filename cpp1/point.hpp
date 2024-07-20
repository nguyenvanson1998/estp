// point.hpp
#pragma once

#include <vector>
#include <cmath>

class Point {
public:
    std::vector<double> axes;
    bool steiner;

    Point(const std::vector<double>& axes = {}, bool steiner = false);
    bool equals(const Point& p) const;
    static Point from_line(const std::string& line);
    void set_axes(const std::vector<double>& axes);
};

double distance(const Point& A, const Point& B);
double dot_product(const Point& A, const Point& B, const Point& C);
double angle(const Point& A, const Point& B, const Point& C);
std::vector<double> center_of_gravity(const std::vector<Point>& points);
std::vector<double> fermat_point(const std::vector<Point>& points);