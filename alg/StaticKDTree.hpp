#pragma once
#include <vector>
#include <tuple>
#include <algorithm>

namespace alg {

class StaticKDTree {

typedef std::tuple<int, int> Point;

public:
  StaticKDTree(std::vector<Point> points);
  
};

}
