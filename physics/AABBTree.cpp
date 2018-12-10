#include "AABBTree.hpp"

AABBTree::AABBTree(std::vector<AABBTree::GeoPtr> list) :
geometry (
  std::reduce(list.begin(), list.end(), 
              &Geometry::smallest_bounding_rectange)
)
{
  AddGeometry(list.begin(), list.end());
}

//AABBTree::
