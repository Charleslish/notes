#include <iostream>
#include <string>
#include <vector>

#include "binary_search_tree.hpp"

int main() {
  BinarySearchTree<int> int_bst;
  for (int v : {20, 10, 30, 5, 15, 25, 35}) {
    int_bst.Insert(v);
  }

  std::cout << "Integer tree:" << std::endl;
  int_bst.PrintTree();
  std::cout << std::endl;

  std::cout << "Remove 5 (leaf):" << std::endl;
  int_bst.Remove(5);
  int_bst.PrintTree();
  std::cout << std::endl;

  std::cout << "Remove 10 (one child, 15):" << std::endl;
  int_bst.Remove(10);
  int_bst.PrintTree();
  std::cout << std::endl;

  std::cout << "Remove 20 (root, two children):" << std::endl;
  int_bst.Remove(20);
  int_bst.PrintTree();
  std::cout << std::endl;

  BinarySearchTree<std::string> str_bst;
  for (const std::string& s : {"mango", "apple", "pear", "banana", "kiwi", "grape", "orange"}) {
    str_bst.Insert(s);
  }
  std::cout << "String tree:" << std::endl;
  str_bst.PrintTree();
  std::cout << std::endl;

  std::cout << "Remove \"mango\" (root, two children):" << std::endl;
  str_bst.Remove("mango");
  str_bst.PrintTree();

  return 0;
}
