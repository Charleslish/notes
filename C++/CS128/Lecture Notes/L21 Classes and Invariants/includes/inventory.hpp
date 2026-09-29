#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <map>
#include <string>

class Inventory {
 public:
  bool AddStock(const std::string& item, int quantity);
  bool Sell(const std::string& item, int quantity);
  bool InStock(const std::string& item) const;
  int GetQuantity(const std::string& item) const;
  int GetTotalItems() const;

 private:
  static constexpr int kMaxQuantity = 999;
  bool HasAtLeast(const std::string& item, int quantity) const;
  void RemoveIfEmpty(const std::string& item);
  std::map<std::string, int> stock_;
};

#endif
