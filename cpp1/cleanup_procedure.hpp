#pragma once

#include "tree.hpp"
#include <vector>

std::pair<Tree, std::vector<Point*>> cleanup(const Tree& T, const std::vector<Point*>& X, const std::vector<Point*>& S);