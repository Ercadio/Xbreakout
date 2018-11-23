#pragma once
#include "Matrix.hpp"
#include <ostream>

/**
 *  @union Geometry
 *  A union used for collision control
 *  @todo Implement contains
 *  @todo Implement intersect
 */
struct Geometry {
  enum Type {
    RECT, ELLIPSE
  };
  Type type;
  Vector pos;
  Vector rad;
  bool contains(const Vector& v) const;
  bool intersect(const Geometry& g) const;
};

std::ostream& operator<<(std::ostream& os, const Geometry& g);
