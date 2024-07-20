// tree.cpp
#include "tree.hpp"
#include <algorithm>

Tree Tree::from_nodes(const std::vector<Point*>& nodes) {
    Tree new_tree;
    for (auto node : nodes) {
        new_tree.adjacency_list[node] = {};
    }
    return new_tree;
}

Tree Tree::copy() const {
    Tree new_tree;
    for (const auto& [node, adjacency] : adjacency_list) {
        new_tree.adjacency_list[node] = adjacency;
    }
    return new_tree;
}

int Tree::degree(Point* node) const {
    return adjacency_list.at(node).size();
}

void Tree::add_node(Point* node) {
    if (adjacency_list.find(node) == adjacency_list.end()) {
        adjacency_list[node] = {};
    }
}

void Tree::remove_node(Point* node) {
    for (auto connected_node : adjacency_list[node]) {
        adjacency_list[connected_node].erase(
            std::remove(adjacency_list[connected_node].begin(),
                        adjacency_list[connected_node].end(), node),
            adjacency_list[connected_node].end());
    }
    adjacency_list.erase(node);
}

void Tree::add_edge(Point* node_1, Point* node_2) {
    adjacency_list[node_1].push_back(node_2);
    adjacency_list[node_2].push_back(node_1);
}

void Tree::remove_edge(Point* node_1, Point* node_2) {
    adjacency_list[node_1].erase(
        std::remove(adjacency_list[node_1].begin(),
                    adjacency_list[node_1].end(), node_2),
        adjacency_list[node_1].end());
    adjacency_list[node_2].erase(
        std::remove(adjacency_list[node_2].begin(),
                    adjacency_list[node_2].end(), node_1),
        adjacency_list[node_2].end());
}

std::vector<std::pair<Point*, Point*>> Tree::edge_list() const {
    std::vector<std::pair<Point*, Point*>> edges;
    for (const auto& [node_1, adjacency] : adjacency_list) {
        for (auto node_2 : adjacency) {
            if (node_1 < node_2) {
                edges.emplace_back(node_1, node_2);
            }
        }
    }
    return edges;
}

double Tree::l() const {
    auto edges = edge_list();
    double length = 0.0;
    for (const auto& edge : edges) {
        length += distance(*edge.first, *edge.second);
    }
    return length;
}