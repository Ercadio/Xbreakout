#include "Geometry.hpp"

bool Geometry::contains(const Vector& v) const {
  
  return false;
}

bool Geometry::intersect(const Geometry& g) const {

  return false;
}

std::ostream& operator<<(std::ostream& os, const Geometry& g) {
  os << "Geometry " << &g << " {\n"
     << "type: " << g.type << ", \n"
     << "pos: " << g.pos << ", \n"
     << "rad: " << g.rad << "\n}"
     << std::endl;
  return os;
}
