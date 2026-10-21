#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "solution.hpp"

int main() {
  std::vector<std::pair<int, std::string>> roster = {
      {1, "Alice"}, {2, "Bob"}, {3, "Charlie"}};
  std::cout << Lookup(roster, 2) << std::endl;  // Bob

  std::vector<std::pair<std::string, int>> scores = {
      {"Alice", 95}, {"Bob", 87}, {"Charlie", 92}};
  std::cout << Lookup(scores, std::string("Charlie")) << std::endl;  // 92

  return 0;
}
