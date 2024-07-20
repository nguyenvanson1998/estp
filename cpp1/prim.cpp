// prim.hpp
#pragma once

#include "tree.hpp"

Tree MST(const std::vector<Point*>& nodes);

// prim.cpp
#include "prim.hpp"
#include <vector>
#include <limits>

Tree MST(const std::vector<Point*>& nodes) {
    int n = nodes.size();
    std::vector<std::vector<double>> adj_matrix(n, std::vector<double>(n));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            adj_matrix[i][j] = distance(*nodes[i], *nodes[j]);
        }
    }

    std::vector<int> parent(n, -1);
    std::vector<bool> mst_set(n, false);
    std::vector<double> node_distance(n, std::numeric_limits<double>::infinity());
    node_distance[0] = 0.0;

    for (int _ = 0; _ < n; ++_) {
        int min_index = -1;
        double min_distance = std::numeric_limits<double>::infinity();
        for (int i = 0; i < n; ++i) {
            if (!mst_set[i] && node_distance[i] < min_distance) {
                min_distance = node_distance[i];
                min_index = i;
            }
        }

        mst_set[min_index] = true;

        for (int i = 0; i < n; ++i) {
            if (!mst_set[i] && adj_matrix[min_index][i] < node_distance[i]) {
                node_distance[i] = adj_matrix[min_index][i];
                parent[i] = min_index;
            }
        }
    }

    Tree mst = Tree::from_nodes(nodes);
    for (int i = 1; i < n; ++i) {
        int j = parent[i];
        mst.add_edge(nodes[i], nodes[j]);
    }

    return mst;
}