#include "forest_trail.hpp"

void ForestTrail::AddLandmark(const std::string& name) {
  PathNode* new_node = new PathNode();
  new_node->landmark = name;

  if (root_ == nullptr) {
    root_ = new_node;
    return;
  }

  PathNode* current = root_;
  PathNode* parent = nullptr;
  while (current != nullptr) {
    parent = current;
    if (name < current->landmark) {
      current = current->left;
    } else {
      current = current->right;
    }
  }

  if (name < parent->landmark) {
    parent->left = new_node;
  } else {
    parent->right = new_node;
  }
}

PathNode* ForestTrail::start() const { return root_; }

static void ClearNodes(PathNode* node) {
  if (node == nullptr) return;
  ClearNodes(node->left);
  ClearNodes(node->right);
  delete node;
}

ForestTrail::~ForestTrail() { ClearNodes(root_); }
