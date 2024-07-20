// point.cpp
#include "point.hpp"
#include <sstream>
#include <algorithm>
#include <numeric>

Point::Point(const std::vector<double>& axes, bool steiner) : axes(axes), steiner(steiner) {}

bool Point::equals(const Point& p) const {
    return axes == p.axes;
}

Point Point::from_line(const std::string& line) {
    std::istringstream iss(line);
    std::vector<double> axes;
    double axis;
    while (iss >> axis) {
        axes.push_back(axis);
    }
    return Point(axes);
}

void Point::set_axes(const std::vector<double>& axes) {
    this->axes = axes;
}

double distance(const Point& A, const Point& B) {
    double sum = 0.0;
    for (size_t i = 0; i < A.axes.size(); ++i) {
        sum += std::pow(A.axes[i] - B.axes[i], 2);
    }
    return std::sqrt(sum);
}

double dot_product(const Point& A, const Point& B, const Point& C) {
    double sum = 0.0;
    for (size_t i = 0; i < A.axes.size(); ++i) {
        sum += (A.axes[i] - B.axes[i]) * (C.axes[i] - B.axes[i]);
    }
    return sum;
}

double angle(const Point& A, const Point& B, const Point& C) {
    if (A.axes == B.axes || A.axes == C.axes || C.axes == B.axes) {
        return M_PI;
    }
    std::vector<double> BA(A.axes.size()), BC(A.axes.size());
    for (size_t i = 0; i < A.axes.size(); ++i) {
        BA[i] = B.axes[i] - A.axes[i];
        BC[i] = B.axes[i] - C.axes[i];
    }
    double norm_BA = std::sqrt(std::inner_product(BA.begin(), BA.end(), BA.begin(), 0.0));
    double norm_BC = std::sqrt(std::inner_product(BC.begin(), BC.end(), BC.begin(), 0.0));
    double dot = std::inner_product(BA.begin(), BA.end(), BC.begin(), 0.0) / (norm_BA * norm_BC);
    return std::acos(std::max(-1.0, std::min(1.0, dot)));
}

std::vector<double> center_of_gravity(const std::vector<Point>& points) {
    std::vector<double> result(points[0].axes.size(), 0.0);
    for (const auto& p : points) {
        for (size_t i = 0; i < p.axes.size(); ++i) {
            result[i] += p.axes[i];
        }
    }
    for (auto& r : result) {
        r /= points.size();
    }
    return result;
}

std::vector<double> fermat_point(const std::vector<Point>& points) {
    if (points.size() != 3) {
        return {};
    }

    const Point& A = points[0];
    const Point& B = points[1];
    const Point& C = points[2];

    double angle_A = angle(B, A, C);
    if (angle_A >= 2 * M_PI / 3) {
        return A.axes;
    }
    double angle_B = angle(A, B, C);
    if (angle_B >= 2 * M_PI / 3) {
        return B.axes;
    }
    double angle_C = angle(A, C, B);
    if (angle_C >= 2 * M_PI / 3) {
        return C.axes;
    }

    double a = distance(B, C);
    double b = distance(A, C);
    double c = distance(A, B);

    double x = 1 / std::sin(angle_A + M_PI / 3);
    double y = 1 / std::sin(angle_B + M_PI / 3);
    double z = 1 / std::sin(angle_C + M_PI / 3);

    double D = a * x + b * y + c * z;

    std::vector<double> result(A.axes.size());
    for (size_t i = 0; i < result.size(); ++i) {
        result[i] = (a * x * A.axes[i] + b * y * B.axes[i] + c * z * C.axes[i]) / D;
    }
    return result;
}