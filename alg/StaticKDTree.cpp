#include "alg.hpp"

namespace alg {

StaticKDTree::StaticKDTree(std::vector<Point> points) {

  // First we sort the points by their x-coord
  std::sort(points.begin(), points.end(), [](const Point& p1, const Point& p2){
    return std::get<0>(p1) < std::get<0>(p2);
  });

  // Next, we sort the points by their y-coord
  std::vector<Point> ySorted{points};
  std::sort(points.begin(), points.end(), [](const Point& p1, const Point& p2){
    return std::get<1>(p1) < std::get<1>(p2);
  });
  

  // Next, we build our tree of nodes
  
  
}

}
