#pragma once

#include "Geometry.hpp"
#include "Matrix.hpp"

/**
 *  @struct RigidBody
 *  A structure that contains information about a physical entity
 */

struct RigidBody {
  Geometry geo;
  Vector vel;
  double mass;
};
