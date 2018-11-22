#pragma once

/**
 *  @class PhysicsEngine
 *  A controller for a set of geometries
 */
class PhysicsEngine {
  std::vector<Geometry*> _objects;
  std::vector<Geometry*> _to_remove;
  void _fast_update();
  void _careful_update();
public:
  void addObject(Geometry& obj);
  void updateGeometries();
  void removeObject(Geometry& obj);
};
