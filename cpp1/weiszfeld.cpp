#include "weiszfeld.hpp"
#include <numeric>
#include <cmath>

Point weiszfeld(Point geo_median, const std::vector<Point>& points) {
    double total_distance = std::accumulate(points.begin(), points.end(), 0.0,
        [&geo_median](double sum, const Point& p) { return sum + distance(geo_median, p); });

    Point new_center(center_of_gravity(points));

    while (true) {
        for (const auto& p : points) {
            if (geo_median.equals(p)) {
                return p;
            }
        }

        std::vector<double> numerator(geo_median.axes.size(), 0.0);
        double denominator = 0.0;

        for (const auto& p : points) {
            double dist = distance(p, geo_median);
            for (size_t i = 0; i < p.axes.size(); ++i) {
                numerator[i] += p.axes[i] / dist;
            }
            denominator += 1.0 / dist;
        }

        for (size_t i = 0; i < new_center.axes.size(); ++i) {
            new_center.axes[i] = numerator[i] / denominator;
        }

        double new_total = std::accumulate(points.begin(), points.end(), 0.0,
            [&new_center](double sum, const Point& p) { return sum + distance(new_center, p); });

        if (total_distance <= new_total + 1e-9) {
            return geo_median;
        }

        geo_median = new_center;
        total_distance = new_total;
    }
}