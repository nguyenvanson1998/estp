#pragma once

#include "tree.hpp"
#include "point.hpp"
#include <vector>

std::pair<Tree, std::vector<Point*>> local_search(const std::vector<Point*>& X, int _k = 3, double _l = 0.3, double _u = 0.6, double _x = 0.0);