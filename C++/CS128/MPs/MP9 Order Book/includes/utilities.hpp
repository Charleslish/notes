#ifndef UTILITIES_HPP_
#define UTILITIES_HPP_

#include <string>

enum class OrderType { kBuy, kSell };

struct Order {
  double price = 0.0;
  unsigned int shares = 0;
  unsigned int order_id = 0;
  OrderType type = OrderType::kBuy;
};

struct Trade {
  double price = 0.0;
  unsigned int shares = 0;
  unsigned int buy_order_id = 0;
  unsigned int sell_order_id = 0;
};

bool operator<(const Order& lhs, const Order& rhs);

std::string FormatPrice(double price);

#endif  // UTILITIES_HPP_
