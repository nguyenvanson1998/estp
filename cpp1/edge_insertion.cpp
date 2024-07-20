#include "edge_insertion.hpp"
#include "point.hpp"
#include "local_optimization.hpp"
#include <cmath>

std::pair<Tree, std::vector<Point*>> edge_insertion(const Tree& T, const std::vector<Point*>& X, const std::vector<Point*>& S) {
    Tree T_ = T;
    std::vector<Point*> S_ = S;

    std::vector<std::pair<Point*, Point*>> edges_to_insert;
    std::vector<Point*> XS = X;
    XS.insert(XS.end(), S.begin(), S.end());

    for (const auto& x_i : XS) {
        for (const auto& x_j : T_.adjacency_list[x_i]) {
            std::vector<Point*> edge_list_xj;
            for (const auto& x_l : T_.adjacency_list[x_j]) {
                if (!x_l->equals(*x_i) && angle(*x_i, *x_j, *x_l) < M_PI * 2 / 3) {
                    edge_list_xj.push_back(x_l);
                }
            }

            if (!edge_list_xj.empty()) {
                Point* x_k = edge_list_xj[0];
                for (const auto& x_l : edge_list_xj) {
                    if (dot_product(*x_i, *x_j, *x_l) > dot_product(*x_i, *x_j, *x_k)) {
                        x_k = x_l;
                    }
                }
                Point* s = new Point(x_j->axes);
                s->steiner = true;

                S_.push_back(s);
                T_.remove_edge(x_i, x_j);
                T_.remove_edge(x_j, x_k);

                T_.add_node(s);
                edges_to_insert.emplace_back(x_i, s);
                edges_to_insert.emplace_back(x_j, s);
                edges_to_insert.emplace_back(x_k, s);
            }
        }
    }

    for (const auto& edge : edges_to_insert) {
        T_.add_edge(edge.first, edge.second);
    }

    S_ = local_optimization(T_, S_);

    return {T_, S_};
}