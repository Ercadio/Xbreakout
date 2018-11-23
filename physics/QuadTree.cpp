#include "QuadTree.hpp"
#include <sstream>

QuadTree::QuadTree(Geometry boundary) :
bound(std::move(boundary))
{ }

void QuadTree::insert(Geometry* geo) {
  if(not contains(geo)) {
    std::stringstream ss;
    ss << "Geometry " << geo << " was forced into QuadTree " << *this;
    throw std::range_error(ss.str());
  }

  if(node == nullptr) {
    node = geo;
  } else {
    
  }
}

bool QuadTree::contains(Geometry* node) {
  return bound.contains(node->pos);
}

std::ostream& operator<<(std::ostream& os, const QuadTree& g) {
  os << "QuadTree " << &g << " { \n"
     << "bound: " << g.bound << ", \n"
     << "node: " << g.node << ", \n"
     << "topLeft: " << g.topLeft << ", \n"
     << "topRight: " << g.topRight << ", \n"
     << "botLeft: " << g.botLeft << ", \n"
     << "botRight: " << g.botRight << "\n}" << std::endl;
  return os;
}
