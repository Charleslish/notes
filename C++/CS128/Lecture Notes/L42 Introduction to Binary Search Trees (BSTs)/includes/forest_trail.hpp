#ifndef FOREST_TRAIL_HPP
#define FOREST_TRAIL_HPP

#include <string>
#include <vector>

#include "path_node.hpp"

class ForestTrail {
 public:
  ForestTrail() = default;
  ~ForestTrail();

  ForestTrail(const ForestTrail& other) = delete;
  ForestTrail& operator=(const ForestTrail& other) = delete;

  void AddLandmark(const std::string& name);
  PathNode* start() const;

 private:
  PathNode* root_ = nullptr;
};

#endif
