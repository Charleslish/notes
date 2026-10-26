#include <iostream>
#include <string>
#include <vector>

#include "exhibit_catalog.hpp"

int main() {
  ExhibitCatalog catalog(5);

  catalog.AddToFront("Star Compass");
  catalog.AddToFront("Iron Crown");
  catalog.AddToFront("Ruby Chalice");
  catalog.AddToFront("Ancient Map");

  std::vector<std::string> tour = catalog.GetTourOrder();
  std::cout << "Tour order:" << std::endl;
  for (const std::string& name : tour) {
    std::cout << "  " << name << std::endl;
  }
  // Expected: Ancient Map, Ruby Chalice, Iron Crown, Star Compass

  std::cout << "Size: " << catalog.GetSize() << std::endl;       // 4
  std::cout << "Capacity: " << catalog.GetCapacity() << std::endl; // 5

  return 0;
}
