#ifndef ORDER_BOOK_HPP_
#define ORDER_BOOK_HPP_

#include <iostream>
#include <string>
#include <vector>

#include "order_bst.hpp"
#include "utilities.hpp"

class OrderBook {
 public:
  OrderBook(const std::string& ticker);
  ~OrderBook() = default;
  OrderBook(const OrderBook& rhs) = default;
  OrderBook& operator=(const OrderBook& rhs) = default;

  void ProcessOrderFile(const std::string& filename);
  unsigned int PlaceOrder(OrderType type, double price, unsigned int shares);
  void CancelOrder(unsigned int order_id);
  void AmendOrder(unsigned int order_id,
                  double new_price,
                  unsigned int new_shares);

  Order GetBestBid() const;
  Order GetBestAsk() const;
  std::vector<Order> GetTopN(OrderType type, unsigned int n) const;
  const std::vector<Trade>& GetTradeLog() const;

  friend std::ostream& operator<<(std::ostream& os, const OrderBook& book);

 private:
  void MatchIncoming(Order& incoming);
  void Rest(Order order);
  static void Collect(TNode<Order>* node, bool reverse, unsigned int n,
                      std::vector<Order>& orders);
  void ProcessLine(const std::string& line);

  OrderBST bids_;
  OrderBST asks_;
  std::string ticker_;
  unsigned int next_order_id_ = 1;
  std::vector<Trade> trade_log_;
};

#endif  // ORDER_BOOK_HPP_
