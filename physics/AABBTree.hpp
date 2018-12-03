#pragma once
#include <memory>

/**
 *  @struct AABBTree
 *  A AABBTree using the Surface Area Heuristic
 */
struct AABBTree {
  struct Node {
    std::weak_ptr<Geometry> geometry;
    
  };

  AABBTree();
  AABBTree(std::vector<Geometry> list);
  void AddGeometry(std::weak_ptr<Geometry> geometry);
  void PruneExpired();
  
};
