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

  /**
   *  Returns true if the point is in the Geometry
   *  @param v the point
   *  @returns true if the point is in the Geometry
   *  @todo implement
   */
  bool contains(const Vector& v) const;

  /**
   *  Returns true if the two Geometry intersect
   *  @param g the other Geometry
   *  @returns true if the two Geometry intersect
   *  @todo implement
   */
  bool intersect(const Geometry& g) const;

  /**
   *  Returns the area of the Geometry
   *  @returns the area
   *  @todo implement
   */
  float area() const;

  /**
   *  Returns the smallest rectangle that contains both Geometry
   *  @param a the first Geometry
   *  @param b the second Geometry
   *  @returns the bounding rectangle Geometry
   *  @todo implement
   */
  static Geometry smallest_bounding_rectange(const Geometry& a, const Geometry& b);
};


std::ostream& operator<<(std::ostream& os, const Geometry& g);

