#pragma once
#include <memory>
#include <forward_list>

#include "RigidBody.hpp"

/**
 *  @class PhysicsEngine
 *  A controller for a set of bodies
 *  @todo investigate an implementation using a QuadTree
 *  @todo If implemented with a QuadTree, investigate using a KDTree
 *  @todo If implemented with KDTree, investigate GJK Algorithm
 */
class PhysicsEngine {

  typedef std::shared_ptr<RigidBody> BodySPtr;
  typedef std::weak_ptr<RigidBody> BodyWPtr;

  std::forward_list<BodyWPtr> _objects;

public:
  
  enum Impl {
    NAIVE
  };

  void addObject(BodySPtr obj);

  template<Impl imp = NAIVE>
  void updateBodies() {
    throw std::logic_error("PhysicsEngine's algorithm isn't implemented");
  }

private:

};

