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
  return boundary.contains(*node->pos);
}
