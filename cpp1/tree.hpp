// tree.hpp
#pragma once

#include "point.hpp"
#include <unordered_map>
#include <vector>

class Tree {
public:
    std::unordered_map<Point*, std::vector<Point*>> adjacency_list;

    Tree() = default;
    static Tree from_nodes(const std::vector<Point*>& nodes);
    Tree copy() const;
    int degree(Point* node) const;
    void add_node(Point* node);
    void remove_node(Point* node);
    void add_edge(Point* node_1, Point* node_2);
    void remove_edge(Point* node_1, Point* node_2);
    std::vector<std::pair<Point*, Point*>> edge_list() const;
    double l() const;
};