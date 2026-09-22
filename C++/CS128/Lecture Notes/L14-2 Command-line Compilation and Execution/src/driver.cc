#include <iostream>
#include "solution.hpp"

int main() {
  const unsigned int kCartonsInStock = 29;
  const unsigned int kCartonsDelivered = 18;
  std::cout << "Cartons on hand: "
            << CartonsOnHand(kCartonsInStock, kCartonsDelivered) << std::endl;
  return 0;
}
