#pragma once
#include "Geometry.hpp"
#include <ostream>

/**
 *  @struct QuadTree
 *  A QuadTree data structure
 *  @todo Implement insert
 *  @todo implement contains
 *  @todo implement operator<<
 */
struct QuadTree {

  QuadTree* topLeft = nullptr;
  QuadTree* topRight = nullptr;
  QuadTree* botLeft = nullptr;
  QuadTree* botRight = nullptr;
  Geometry* node = nullptr;
  Geometry bound;
  QuadTree(Geometry boundary);
  void insert(Geometry* node);
  bool contains(Geometry* node);

};

std::ostream& operator<<(std::ostream& os, const QuadTree& g);

