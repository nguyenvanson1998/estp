// main.cpp
#include <iostream>
#include "point.hpp"
#include "tree.hpp"
#include "prim.hpp"

int main() {
    Point A({1.0, 3.0, 1.0, 2.0});
    Point B({2.0, 3.0, 2.0, 2.0});
    Point C({1.0, 3.0, 2.0, 2.0});

    std::vector<double> F_axes = fermat_point({A, B, C});
    Point F(F_axes);

    std::cout << "Fermat point: ";
    for (double axis : F.axes) {
        std::cout << axis << " ";
    }
    std::cout << std::endl;

    double ab = distance(A, B);
    double bc = distance(B, C);
    double ca = distance(C, A);

    std::cout << "Distance F to A + B + C: " << distance(F, A) + distance(F, B) + distance(F, C) << std::endl;
    std::cout << "AB + BC: " << ab + bc << std::endl;
    std::cout << "BC + CA: " << bc + ca << std::endl;
    std::cout << "AB + CA: " << ab + ca << std::endl;

    std::vector<Point*> nodes = {&A, &B, &C};
    Tree mst = MST(nodes);
    std::cout << "MST length (3 points): " << mst.l() << std::endl;

    nodes.push_back(&F);
    mst = MST(nodes);
    std::cout << "MST length (4 points): " << mst.l() << std::endl;

    return 0;
}