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

  template<Impl imp>
  void updateBodies() {
    throw std::logic_error("PhysicsEngine's algorithm isn't implemented");
  }

private:

};

/**
 * Implements collision detection in O(n^2)
 */
template<>
void PhysicsEngine::updateBodies<PhysicsEngine::NAIVE>() {
  _objects.remove_if([](BodyWPtr p){ return p.expired(); });
  BodySPtr target, actor;
  for(auto ptarget = _objects.begin(); ptarget != _objects.end(); ++ptarget) {
    if(ptarget->expired())
      continue;
    target = ptarget->lock();
    for(auto pactor = _objects.begin(); pactor != _objects.end(); ++pactor) {
      if(pactor == ptarget)
        continue;
      if(pactor->expired())
        continue;
      actor = pactor->lock();
      // Collision detection
      if(actor->geo.intersect(target->geo)) {
        Vector pos_d = (actor->geo.pos - target->geo.pos);
        Vector vel_d = (actor->vel - target->vel);
        double total_mass = actor->mass + target->mass;

        /**
         *  This formula was found on Wikipedia for perfectly elastic collisions
         *  https://en.wikipedia.org/wiki/Elastic_collision#Two-dimensional_collision_with_two_moving_objects
         */
        actor->vel = 
          actor->vel - 2 * target->mass / total_mass * vel_d.dot(pos_d) / pos_d.dot(pos_d) * pos_d;
        target->vel = 
          target->vel + 2 * target->mass / total_mass * vel_d.dot(pos_d) / pos_d.dot(pos_d) * pos_d;
        break;
      }
    }

    // Update position
    target->geo.pos = target->geo.pos + target->vel;
  }
}
