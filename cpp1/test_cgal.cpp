#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/point_generators_2.h>
#include <CGAL/algorithm.h>
#include <vector>
#include <iostream>

// Kernel type
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

// Triangulation type
typedef CGAL::Delaunay_triangulation_2<K> Delaunay;

// Point type
typedef K::Point_2 Point;

int main() {
    // Create a vector of points
    std::vector<Point> points;
    points.push_back(Point(0, 0));
    points.push_back(Point(1, 0));
    points.push_back(Point(0, 1));
    points.push_back(Point(1, 1));
    points.push_back(Point(0.5, 0.5));

    // Perform Delaunay triangulation
    Delaunay triangulation;
    triangulation.insert(points.begin(), points.end());

    // Print out the points of the triangulation
    for(auto it = triangulation.finite_vertices_begin(); it != triangulation.finite_vertices_end(); ++it) {
        std::cout << it->point() << std::endl;
    }

    return 0;
}
