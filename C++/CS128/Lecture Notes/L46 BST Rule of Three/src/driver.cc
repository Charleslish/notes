#include <iostream>
#include <string>

#include "binary_search_tree.hpp"

int main() {
  // Integer tree: copy ctor and copy assignment.
  BinarySearchTree<int> int_source;
  for (int v : {20, 10, 30, 5, 15}) {
    int_source.Insert(v);
  }

  std::cout << "Integer source:" << std::endl;
  int_source.PrintTree();
  std::cout << std::endl;

  BinarySearchTree<int> int_copy(int_source);
  std::cout << "Integer copy (via copy ctor):" << std::endl;
  int_copy.PrintTree();
  std::cout << std::endl;

  int_source.Insert(25);
  std::cout << "int_source after Insert(25):" << std::endl;
  int_source.PrintTree();
  std::cout << "int_copy (should be unchanged):" << std::endl;
  int_copy.PrintTree();
  std::cout << std::endl;

  BinarySearchTree<int> int_dest;
  int_dest.Insert(100);
  int_dest = int_source;
  std::cout << "int_dest after int_dest = int_source:" << std::endl;
  int_dest.PrintTree();
  std::cout << std::endl;

  // String tree: demonstrate the templated BST with a different type.
  BinarySearchTree<std::string> str_source;
  for (const std::string& s : {"mango", "apple", "pear", "banana", "kiwi"}) {
    str_source.Insert(s);
  }
  std::cout << "String source:" << std::endl;
  str_source.PrintTree();
  std::cout << std::endl;

  BinarySearchTree<std::string> str_copy(str_source);
  std::cout << "String copy (via copy ctor):" << std::endl;
  str_copy.PrintTree();
  std::cout << std::endl;

  BinarySearchTree<std::string> str_dest;
  str_dest.Insert("zebra");
  str_dest = str_source;
  std::cout << "str_dest after str_dest = str_source:" << std::endl;
  str_dest.PrintTree();

  return 0;
}
