#include "local_optimization.hpp"
#include <cmath>
#include <algorithm>

std::vector<Point*> local_optimization(Tree& T, std::vector<Point*>& S) {
    double length = std::numeric_limits<double>::infinity();

    while (T.l() < length - 1e-9) {
        length = T.l();

        for (auto s : S) {
            if (T.degree(s) == 3) {
                std::vector<Point*> neighbors(T.adjacency_list[s].begin(), T.adjacency_list[s].end());
                std::vector<Point> neighbor_points;
                for (auto p : neighbors) {
                    neighbor_points.push_back(*p);
                }
                std::vector<double> new_s = fermat_point(neighbor_points);
                s->set_axes(new_s);
            } else {
                std::vector<Point> neighbors;
                for (auto p : T.adjacency_list[s]) {
                    neighbors.push_back(*p);
                }
                Point new_s = weiszfeld(*s, neighbors);
                s->set_axes(new_s.axes);
            }
        }
    }

    std::vector<Point*> removed_nodes;
    for (auto s : S) {
        for (auto p : T.adjacency_list[s]) {
            if (s->equals(*p)) {
                removed_nodes.push_back(s);
                T.remove_edge(s, p);
                for (auto q : T.adjacency_list[s]) {
                    T.add_edge(p, q);
                }
                T.remove_node(s);
                break;
            }
        }
    }

    std::vector<Point*> temp_S;
    auto it = removed_nodes.begin();
    for (auto s : S) {
        if (it != removed_nodes.end() && s == *it) {
            ++it;
        } else {
            temp_S.push_back(s);
        }
    }
    return temp_S;
}