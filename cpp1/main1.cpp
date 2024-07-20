#include <iostream>
#include <vector>
#include "point.hpp"
#include "tree.hpp"
#include "prim.hpp"
#include "weiszfeld.hpp"
#include "local_optimization.hpp"

void print_point(const Point& p, const std::string& name) {
    std::cout << name << ": (";
    for (size_t i = 0; i < p.axes.size(); ++i) {
        std::cout << p.axes[i];
        if (i < p.axes.size() - 1) std::cout << ", ";
    }
    std::cout << ")" << std::endl;
}

int main() {
    // Test Weiszfeld algorithm
    std::cout << "Testing Weiszfeld algorithm:" << std::endl;
    Point p1({0, 0});
    Point p2({1, 1});
    Point p3({2, 0});
    Point initial_median({1, 0});
    std::vector<Point> points = {p1, p2, p3};
    
    Point geometric_median = weiszfeld(initial_median, points);
    print_point(geometric_median, "Geometric median");
    
    // Test Local Optimization
    std::cout << "\nTesting Local Optimization:" << std::endl;
    Point A({0, 0});
    Point B({4, 0});
    Point C({2, 3});
    Point S({2, 1}); // Initial Steiner point
    
    Tree T;
    T.add_node(&A);
    T.add_node(&B);
    T.add_node(&C);
    T.add_node(&S);
    T.add_edge(&A, &S);
    T.add_edge(&B, &S);
    T.add_edge(&C, &S);
    
    std::vector<Point*> steiner_points = {&S};
    
    std::cout << "Initial tree length: " << T.l() << std::endl;
    print_point(S, "Initial Steiner point");
    
    std::vector<Point*> optimized_steiner_points = local_optimization(T, steiner_points);
    
    std::cout << "Optimized tree length: " << T.l() << std::endl;
    if (!optimized_steiner_points.empty()) {
        print_point(*optimized_steiner_points[0], "Optimized Steiner point");
    } else {
        std::cout << "No Steiner points after optimization" << std::endl;
    }
    
    return 0;
}