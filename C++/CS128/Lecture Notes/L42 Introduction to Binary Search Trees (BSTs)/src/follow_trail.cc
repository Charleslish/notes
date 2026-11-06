#include "follow_trail.hpp"

std::vector<std::string> FollowTrail(const PathNode* start,
                                     const std::vector<std::string>& route) {
  std::vector<std::string> visited;
  if (start == nullptr || route.empty()) {
    return visited;
  }

  const PathNode* current = start;
  visited.push_back(current->landmark);
  for (std::vector<std::string>::size_type i = 1; i < route.size(); ++i) {
    if (current->left != nullptr && current->left->landmark == route[i]) {
      current = current->left;
    } else if (current->right != nullptr &&
               current->right->landmark == route[i]) {
      current = current->right;
    } else {
      break;
    }
    visited.push_back(current->landmark);
  }
  return visited;
}
