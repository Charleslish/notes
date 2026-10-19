#include <iostream>

#include "solution.hpp"

int main() {
  IntArray ia;
  ia.PushBack(7);
  ia.PushBack(11);
  for (unsigned int i = 0; i < ia.GetSize(); ++i) {
    std::cout << ia[i] << std::endl;
  }
  std::cout << "Capacity: " << ia.GetCapacity() << std::endl;
  std::cout << "============================================" << std::endl;
  ia.PushBack(12);
  for (unsigned int i = 0; i < ia.GetSize(); ++i) {
    std::cout << ia[i] << std::endl;
  }
  std::cout << "Capacity: " << ia.GetCapacity() << std::endl;
}