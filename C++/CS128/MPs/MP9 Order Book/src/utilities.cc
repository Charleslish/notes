#include "utilities.hpp"

#include <sstream>

bool operator<(const Order& lhs, const Order& rhs) {
  return lhs.price < rhs.price;
}

std::string FormatPrice(double price) {
  std::ostringstream oss;
  oss.setf(std::ios::fixed);
  oss.precision(2);
  oss << "$" << price;
  return oss.str();
}
