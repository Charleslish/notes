#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "solution.hpp"

int main() {
  std::vector<std::string> shelf {"Middlemarch", "Ulysses", "Walden"};
  std::vector<std::string> hold_cart {"Villette"};
  std::set<std::string> requested {"Ulysses", "Walden"};
  PullHolds(shelf, hold_cart, requested);
  std::cout << "shelf:";
  for (unsigned int i = 0; i < shelf.size(); ++i) {
    std::cout << " " << shelf[i];
  }
  std::cout << std::endl;
  std::cout << "hold cart:";
  for (unsigned int i = 0; i < hold_cart.size(); ++i) {
    std::cout << " " << hold_cart[i];
  }
  std::cout << std::endl;
  return 0;
}
