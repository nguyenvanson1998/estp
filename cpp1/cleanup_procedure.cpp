#include "cleanup_procedure.hpp"
#include "point.hpp"
#include "prim.hpp"
#include "local_optimization.hpp"

bool exists_steiner_degree_under_3(const Tree& T, const std::vector<Point*>& S) {
    for (const auto& s : S) {
        if (T.degree(s) < 3) {
            return true;
        }
    }
    return false;
}

bool exists_steiner_edge(const Tree& T) {
    for (const auto& edge : T.edge_list()) {
        if (edge.first->steiner && edge.second->steiner) {
            return true;
        }
    }
    return false;
}

std::pair<Tree, std::vector<Point*>> cleanup(const Tree& T, const std::vector<Point*>& X, const std::vector<Point*>& S) {
    Tree T_ = T;
    std::vector<Point*> S_ = S;

    while (exists_steiner_degree_under_3(T_, S_)) {
        std::vector<Point*> removed_nodes;
        for (auto it = S_.begin(); it != S_.end();) {
            Point* s = *it;
            if (T_.degree(s) == 1) {
                T_.remove_node(s);
                removed_nodes.push_back(s);
                it = S_.erase(it);
            } else if (T_.degree(s) == 2) {
                auto neighbors = T_.adjacency_list[s];
                T_.remove_node(s);
                T_.add_edge(neighbors[0], neighbors[1]);
                removed_nodes.push_back(s);
                it = S_.erase(it);
            } else {
                ++it;
            }
        }

        for (auto& s : S_) {
            if (T_.degree(s) == 3) {
                std::vector<Point> neighbors;
                for (const auto& neighbor : T_.adjacency_list[s]) {
                    neighbors.push_back(*neighbor);
                }
                s->set_axes(fermat_point(neighbors));
            }
        }

        std::vector<Point*> XS = X;
        XS.insert(XS.end(), S_.begin(), S_.end());
        T_ = MST(XS);
    }

    if (exists_steiner_edge(T_)) {
        S_ = local_optimization(T_, S_);
    }

    return {T_, S_};
}