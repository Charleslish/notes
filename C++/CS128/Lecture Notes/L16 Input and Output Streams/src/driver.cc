#include <iostream>
#include <sstream>

#include "solution.hpp"

int main() {
  std::istringstream in("12\n7\nalpha\n9\n");
  std::vector<int> readings = ReadReadings(in);
  for (unsigned int i = 0; i < readings.size(); ++i) {
    std::cout << readings[i] << std::endl;
  }
  return 0;
}
