#include <iostream>

#include "inventory.hpp"

int main() {
  const int kPotionsBought = 12;
  const int kPotionsSold = 5;
  const int kTooManyArrows = 1000;

  Inventory inventory;
  const bool bought = inventory.AddStock("potion", kPotionsBought);
  const bool sold = inventory.Sell("potion", kPotionsSold);
  const bool overfilled = inventory.AddStock("arrow", kTooManyArrows);

  std::cout << "bought: " << bought << ", sold: " << sold
            << ", overfilled: " << overfilled << std::endl;
  std::cout << "potion: " << inventory.GetQuantity("potion") << std::endl;
  std::cout << "arrow in stock: " << inventory.InStock("arrow") << std::endl;
  std::cout << "total: " << inventory.GetTotalItems() << std::endl;
  return 0;
}
