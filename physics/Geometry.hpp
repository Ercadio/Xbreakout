#pragma once
#include "Matrix.hpp"

/**
 *  @union Geometry
 *  A union used for collision control
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
