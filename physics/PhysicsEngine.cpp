#include "PhysicsEngine.hpp"

void PhysicsEngine::addObject(BodySPtr obj) { _objects.emplace_after(_objects.end(), obj); }

