#pragma once
#include <memory>
#include "Geometry.hpp"
#include <vector>
#include <stack>

/**
 *  @struct AABBTree
 *  A AABBTree using the Surface Area Heuristic
 */
struct AABBTree {

  AABBTree* left = nullptr;
  AABBTree* right = nullptr;
  using GeoPtr = std::weak_ptr<Geometry>;
  GeoPtr geometry;

  /**
   *  Creates an AABBTree from the list of Geometry
   *  @param list the list of std::weak_ptr<Geometry>
   */
  AABBTree(std::vector<std::weak_ptr<Geometry> > list);

  /**
   *  Adds the Geometry to the AABBTree
   *  @param geometry the std::weak_ptr<Geometry>
   */
  void AddGeometry(std::weak_ptr<Geometry> geometry);

  /**
   *  Adds all the Geometry in the Iterable
   *  @tparam Iterator the Iterator type
   *  @param begin the beginning of the Iterable
   *  @param end the end of the Iterable
   *  @requires Iterator to dereference to a std::weak_ptr<Geometry>
   *  @requires std::iterator_traits<Iterator>::iterator_category to be std::input_iterator_tag
   */
  template <class Iterator>
  void AddGeometry(Iterator begin, Iterator end);

  void PruneExpired();
  
  struct {
    class Iterator {
      std::stack<AABBTree*> parents;
      AABBTree* data = nullptr;
    public:
      Iterator() = default;
      Iterator(const Iterator&) = default;
      Iterator& operator=(const Iterator&) = default;
      bool operator==(const Iterator& other) { return other.data == this->data; }
      bool operator!=(const Iterator& other) { return not(*this == other); }
      GeoPtr& operator*() { return data->geometry; }
      Iterator& operator++();
      Iterator operator++(int);
    };
    Iterator begin();
    Iterator end();
  } Geometries;
};

