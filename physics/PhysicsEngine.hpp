#pragma once

/**
 *  @class PhysicsEngine
 *  A controller for a set of geometries
 *  @todo Implement addObject
 *  @todo Implement updateGeometries
 *  @todo Implement removeObject
 *  @todo Implement _fast_update() and _carefule_update()
 *  @todo Consider making this a bridge
 *  @todo If made a bridge, create a Naive O(n^2) implementation
 *  @todo If made a bridge, investigate a solution using a QuadTree
 *  @todo If implemented with a QuadTree, investigate using a KDTree
 *  @todo If implemented with KDTree, investigate GJK Algorithm
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
