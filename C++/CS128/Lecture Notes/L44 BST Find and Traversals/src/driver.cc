#include <iostream>
#include <vector>

#include "find_bst.hpp"

int main() {
  FindBST<int> bst;
  std::vector<int> values = {10, 5, 15, 3, 7, 12, 20};
  for (int v : values) {
    bst.Insert(v);
  }

  std::cout << "Tree:" << std::endl;
  bst.PrintTree();
  std::cout << std::endl;

  const int* found_7 = bst.Find(7);
  const int* found_8 = bst.Find(8);
  std::cout << "Find(7): " << (found_7 != nullptr ? "found" : "not found")
            << std::endl;
  std::cout << "Find(8): " << (found_8 != nullptr ? "found" : "not found")
            << std::endl;

  const int* min_value = bst.FindMin();
  const int* max_value = bst.FindMax();
  std::cout << "Min: " << (min_value != nullptr ? std::to_string(*min_value) : "(empty)") << std::endl;
  std::cout << "Max: " << (max_value != nullptr ? std::to_string(*max_value) : "(empty)") << std::endl;
  std::cout << "Height: " << bst.Height() << std::endl;

  std::vector<int> inorder = bst.InorderTraversal();
  std::cout << "Inorder: ";
  for (int v : inorder) std::cout << v << " ";
  std::cout << std::endl;

  std::vector<int> preorder = bst.PreorderTraversal();
  std::cout << "Preorder: ";
  for (int v : preorder) std::cout << v << " ";
  std::cout << std::endl;

  std::vector<int> postorder = bst.PostorderTraversal();
  std::cout << "Postorder: ";
  for (int v : postorder) std::cout << v << " ";
  std::cout << std::endl;

  return 0;
}
