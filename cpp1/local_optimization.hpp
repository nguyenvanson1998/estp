#pragma once

#include "tree.hpp"
#include "point.hpp"
#include "weiszfeld.hpp"
#include <vector>

std::vector<Point*> local_optimization(Tree& T, std::vector<Point*>& S);