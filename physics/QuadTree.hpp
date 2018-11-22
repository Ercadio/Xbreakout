#pragma once
#include "Geometry.hpp"

template <class T>
struct QuadTree {

  QuadTree* topLeft = nullptr;
  QuadTree* topRight = nullptr;
  QuadTree* botLeft = nullptr;
  QuadTree* botRight = nullptr;
  Geometry* node = nullptr;
  Geometry bound;
  QuadTree(Vector bound_TL, Vector bound_TR);
  void insert(Geometry* node);
  bool in(Geometry* node);

};
