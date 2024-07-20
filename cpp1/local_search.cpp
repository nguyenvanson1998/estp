#include "local_search.hpp"
#include "prim.hpp"
#include "cleanup_procedure.hpp"
#include "edge_insertion.hpp"
#include "steiner_topology_recovery.hpp"
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <random>
#include <cmath>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Delaunay_triangulation;
typedef K::Point_2 CGALPoint;

std::pair<Tree, std::vector<Point*>> local_search(const std::vector<Point*>& X, int _k, double _l, double _u, double _x) {
    int counter = 1;
    std::vector<Point*> S;
    Tree T = MST(X);

    int trial_limit = _k * std::sqrt(X.size());

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(_l, _u);

    while (counter <= trial_limit) {
        std::vector<Point*> S_ = S;
        std::vector<Point*> point_list = X;
        point_list.insert(point_list.end(), S.begin(), S.end());

        std::vector<CGALPoint> cgal_points;
        for (const auto& p : point_list) {
            cgal_points.emplace_back(p->axes[0], p->axes[1]);
        }

        Delaunay_triangulation dt;
        dt.insert(cgal_points.begin(), cgal_points.end());

        double p = (_l == _u) ? _l : dis(gen);

        for (auto it = dt.finite_faces_begin(); it != dt.finite_faces_end(); ++it) {
            std::vector<Point*> simplex;
            for (int i = 0; i < 3; ++i) {
                int index = std::distance(cgal_points.begin(), std::find(cgal_points.begin(), cgal_points.end(), it->vertex(i)->point()));
                simplex.push_back(point_list[index]);
            }

            std::vector<Point> points;
            for (auto p : simplex) {
                points.push_back(*p);
            }

            Point* s = new Point(center_of_gravity(points));
            s->steiner = true;
            if (dis(gen) < p) {
                S_.push_back(s);
            }
        }

        std::vector<Point*> XS = X;
        XS.insert(XS.end(), S_.begin(), S_.end());
        Tree T_ = MST(XS);

        auto [T_cleaned, S_cleaned] = cleanup(T_, X, S_);
        auto [T_inserted, S_inserted] = edge_insertion(T_cleaned, X, S_cleaned);

        double l_T = T.l();

        if (T_inserted.l() - l_T < _x * l_T) {
            auto [T_recovered, S_recovered] = recover(T_inserted, X, S_inserted);
            T_ = T_recovered;
            S_ = S_recovered;
        }

        if (T_.l() - l_T < -1e-9) {
            S = S_;
            T = T_;
            counter = 1;
        } else {
            counter++;
        }
    }

    return {T, S};
}