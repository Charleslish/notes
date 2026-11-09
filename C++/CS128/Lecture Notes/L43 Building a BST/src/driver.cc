#include <iostream>
#include <string>
#include <vector>
#include "grandparent_bst.hpp"
int main() {
  GrandparentBST<int> bst;
  std::vector<int> values = {10, 5, 15, 3, 7, 12, 20};
  for (int value : values)
    bst.InsertWithGrandparent(value);
  std::cout << "Tree:" << std::endl;
  bst.PrintTree();
  return 0;
}
