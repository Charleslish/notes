#include <iostream>
#include <string>
#include <vector>
#include <set>

#include "solution.hpp"

int main() {
  std::vector<std::string> draft {"the", "cat", "saw", "the", "dog"};
  std::vector<std::string> listed = UsedOnce(draft);
  std::cout << "words used once: " << listed.size() << std::endl;
  for (unsigned int i = 0; i < listed.size(); ++i) {
    std::cout << listed[i] << std::endl;
  }
  return 0;
}
