#include <iostream>

#include "order_book.hpp"

int main() {
  OrderBook book("ILLINI");

  // Place some orders that don't match (buy prices below sell prices).
  book.PlaceOrder(OrderType::kSell, 51.00, 100);  // order #1
  book.PlaceOrder(OrderType::kSell, 50.00, 70);   // order #2
  book.PlaceOrder(OrderType::kBuy, 48.00, 200);   // order #3

  std::cout << "--- After 3 non-matching orders ---\n";
  std::cout << book << "\n";

  // Place a buy that crosses the best ask -- triggers matching.
  book.PlaceOrder(OrderType::kBuy, 50.50, 120);  // order #4

  std::cout << "--- After aggressive buy ---\n";
  std::cout << book << "\n";

  // Cancel an order.
  book.CancelOrder(3);

  std::cout << "--- After canceling order #3 ---\n";
  std::cout << book << "\n";

  return 0;
}
