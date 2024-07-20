#include "steiner_topology_recovery.hpp"
#include "point.hpp"
#include "local_optimization.hpp"

std::pair<Tree, std::vector<Point*>> recover(const Tree& T, const std::vector<Point*>& X, const std::vector<Point*>& S) {
    Tree T_ = T;
    std::vector<Point*> S_ = S;

    std::vector<Point*> XS = X;
    XS.insert(XS.end(), S.begin(), S.end());

    for (const auto& x_i : XS) {
        if (T.degree(x_i) > 3) {
            std::vector<Point*> edge_list_xi = T.adjacency_list.at(x_i);
            for (int _ = 0; _ < T.degree(x_i) - 3; ++_) {
                Point* x_k = edge_list_xi[0];
                Point* x_l = edge_list_xi[1];

                int length = edge_list_xi.size();
                for (int k = 0; k < length; ++k) {
                    Point* x_kk = edge_list_xi[k];
                    for (int l = k + 1; l < length; ++l) {
                        Point* x_ll = edge_list_xi[l];
                        if (dot_product(*x_kk, *x_i, *x_ll) > dot_product(*x_k, *x_i, *x_l)) {
                            x_k = x_kk;
                            x_l = x_ll;
                        }
                    }
                }

                Point* s = new Point(x_i->axes);
                s->steiner = true;
                S_.push_back(s);

                T_.remove_edge(x_i, x_k);
                T_.remove_edge(x_i, x_l);
                edge_list_xi.erase(std::remove(edge_list_xi.begin(), edge_list_xi.end(), x_k), edge_list_xi.end());
                edge_list_xi.erase(std::remove(edge_list_xi.begin(), edge_list_xi.end(), x_l), edge_list_xi.end());

                T_.add_node(s);
                T_.add_edge(x_i, s);
                T_.add_edge(x_k, s);
                T_.add_edge(x_l, s);
            }
        }
    }

    S_ = local_optimization(T_, S_);

    return {T_, S_};
}