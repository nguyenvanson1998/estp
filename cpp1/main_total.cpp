#include <iostream>
#include "point.hpp"
#include "tree.hpp"
#include "local_search.hpp"
void print_points(const std::vector<Point*>& S) {
    for (const auto& p : S) {
        for (size_t i = 0; i < p->axes.size(); ++i) {
            std::cout << p->axes[i];
            if (i < p->axes.size() - 1) {
                std::cout << ' ';
            }
        }
        std::cout << std::endl;
    }
}
int main() {
    std::vector<Point*> X;
    X.push_back(new Point({0, 0}));
    X.push_back(new Point({1, 0}));
    X.push_back(new Point({0, 1}));
    X.push_back(new Point({1, 1}));

    auto [T, S] = local_search(X);

    std::cout << "Optimized tree length: " << T.l() << std::endl;
    std::cout << "Number of Steiner points: " << S.size() << std::endl;
    print_points(S);
    // Clean up
    for (auto p : X) delete p;
    for (auto s : S) delete s;

    return 0;
}