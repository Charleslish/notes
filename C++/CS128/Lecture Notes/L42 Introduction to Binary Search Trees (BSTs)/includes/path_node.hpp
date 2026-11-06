#ifndef PATH_NODE_HPP
#define PATH_NODE_HPP

#include <string>

struct PathNode {
  std::string landmark;
  PathNode* left = nullptr;
  PathNode* right = nullptr;
};

#endif
