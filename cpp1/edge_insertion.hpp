#pragma once

#include "tree.hpp"
#include <vector>

std::pair<Tree, std::vector<Point*>> edge_insertion(const Tree& T, const std::vector<Point*>& X, const std::vector<Point*>& S);