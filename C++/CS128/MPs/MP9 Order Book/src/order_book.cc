#include "order_book.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>

OrderBook::OrderBook(const std::string& ticker) : ticker_(ticker) {}

void OrderBook::ProcessOrderFile(const std::string& filename) {
  std::ifstream file(filename);
  if (!file)
    throw std::runtime_error("Unable to open file");
  std::string line;
  while (std::getline(file, line))
    if (!line.empty())
      ProcessLine(line);
}

void OrderBook::ProcessLine(const std::string& line) {
  std::stringstream stream(line);
  std::vector<std::string> fields;
  std::string field;
  while (std::getline(stream, field, ','))
    fields.push_back(field);
  if (!line.empty() && line.back() == ',')
    fields.push_back("");
  try {
    if (fields.size() == 4 && fields[0] == "PLACE") {
      if (fields[1] != "BUY" && fields[1] != "SELL")
        throw std::runtime_error("Invalid side");
      size_t a = 0, b = 0;
      double price = std::stod(fields[2], &a);
      unsigned long shares = std::stoul(fields[3], &b);
      if (a != fields[2].size() || b != fields[3].size() || shares > 4294967295UL || fields[3][0] == '-')
        throw std::runtime_error("Invalid number");
      PlaceOrder(fields[1] == "BUY" ? OrderType::kBuy : OrderType::kSell, price, static_cast<unsigned int>(shares));
    }
    else if (fields.size() == 2 && fields[0] == "CANCEL") {
      size_t a = 0;
      unsigned long id = std::stoul(fields[1], &a);
      if (a != fields[1].size() || id > 4294967295UL || fields[1][0] == '-')
        throw std::runtime_error("Invalid id");
      CancelOrder(static_cast<unsigned int>(id));
    }
    else if (fields.size() == 4 && fields[0] == "AMEND") {
      size_t a = 0, b = 0, c = 0;
      unsigned long id = std::stoul(fields[1], &a);
      double price = std::stod(fields[2], &b);
      unsigned long shares = std::stoul(fields[3], &c);
      if (a != fields[1].size() || b != fields[2].size() || c != fields[3].size() || id > 4294967295UL || shares > 4294967295UL || fields[1][0] == '-' || fields[3][0] == '-')
        throw std::runtime_error("Invalid number");
      AmendOrder(static_cast<unsigned int>(id), price, static_cast<unsigned int>(shares));
    }
    else
      throw std::runtime_error("Invalid operation");
  }
  catch (const std::exception&) {
    throw std::runtime_error("Invalid order line");
  }
}

void OrderBook::Rest(Order order) {
  if (order.shares == 0)
    return;
  TNode<Order>* node = new TNode<Order>(order);
  if (order.type == OrderType::kBuy)
    bids_.Insert(node);
  else
    asks_.Insert(node);
}
unsigned int OrderBook::PlaceOrder(OrderType type, double price, unsigned int shares) {
  if (shares == 0)
    throw std::runtime_error("Zero shares");
  unsigned int id = next_order_id_++;
  Order order{.price = price, .shares = shares, .order_id = id, .type = type};
  MatchIncoming(order);
  Rest(order);
  return id;
}
void OrderBook::CancelOrder(unsigned int order_id) {
  TNode<Order>* node = bids_.FindById(order_id);
  if (node != nullptr) {
    bids_.Remove(node);
    return;
  }
  node = asks_.FindById(order_id);
  if (node == nullptr)
    throw std::runtime_error("Unknown order");
  asks_.Remove(node);
}
void OrderBook::AmendOrder(unsigned int order_id, double new_price, unsigned int new_shares) {
  if (new_shares == 0)
    throw std::runtime_error("Zero shares");
  TNode<Order>* node = bids_.FindById(order_id);
  if (node == nullptr)
    node = asks_.FindById(order_id);
  if (node == nullptr)
    throw std::runtime_error("Unknown order");
  Order order = node->value;
  CancelOrder(order_id);
  order.price = new_price;
  order.shares = new_shares;
  MatchIncoming(order);
  Rest(order);
}
void OrderBook::MatchIncoming(Order& incoming) {
  OrderBST& opposite = incoming.type == OrderType::kBuy ? asks_ : bids_;
  while (incoming.shares != 0 && !opposite.IsEmpty()) {
    TNode<Order>* node = incoming.type == OrderType::kBuy ? opposite.FindMin() : opposite.FindMax();
    if ((incoming.type == OrderType::kBuy && incoming.price < node->value.price) ||
        (incoming.type == OrderType::kSell && incoming.price > node->value.price))
      break;
    unsigned int quantity = incoming.shares < node->value.shares ? incoming.shares : node->value.shares;
    Trade trade{.price = node->value.price, .shares = quantity,
                .buy_order_id = incoming.type == OrderType::kBuy ? incoming.order_id : node->value.order_id,
                .sell_order_id = incoming.type == OrderType::kSell ? incoming.order_id : node->value.order_id};
    trade_log_.push_back(trade);
    incoming.shares -= quantity;
    node->value.shares -= quantity;
    if (node->value.shares == 0)
      opposite.Remove(node);
  }
}
Order OrderBook::GetBestBid() const {
  if (bids_.IsEmpty())
    throw std::runtime_error("No bids");
  return bids_.FindMax()->value;
}
Order OrderBook::GetBestAsk() const {
  if (asks_.IsEmpty())
    throw std::runtime_error("No asks");
  return asks_.FindMin()->value;
}
void OrderBook::Collect(TNode<Order>* node, bool reverse, unsigned int n, std::vector<Order>& orders) {
  if (node == nullptr || orders.size() >= n)
    return;
  Collect(reverse ? node->right : node->left, reverse, n, orders);
  if (orders.size() < n)
    orders.push_back(node->value);
  Collect(reverse ? node->left : node->right, reverse, n, orders);
}
std::vector<Order> OrderBook::GetTopN(OrderType type, unsigned int n) const {
  std::vector<Order> orders;
  TNode<Order>* node = type == OrderType::kBuy ? bids_.FindMax() : asks_.FindMin();
  while (node != nullptr && orders.size() < n) {
    orders.push_back(node->value);
    if (type == OrderType::kBuy && node->left != nullptr) {
      node = node->left;
      while (node->right != nullptr)
        node = node->right;
    }
    else if (type == OrderType::kSell && node->right != nullptr) {
      node = node->right;
      while (node->left != nullptr)
        node = node->left;
    }
    else {
      TNode<Order>* parent = node->parent;
      while (parent != nullptr && (type == OrderType::kBuy ? node == parent->left : node == parent->right)) {
        node = parent;
        parent = parent->parent;
      }
      node = parent;
    }
  }
  return orders;
}
const std::vector<Trade>& OrderBook::GetTradeLog() const { return trade_log_; }
std::ostream& operator<<(std::ostream& os, const OrderBook& book) {
  os << "=== " << book.ticker_ << " ===\n--- ASKS (best to worst, up to 5) ---\n";
  for (const Order& order : book.GetTopN(OrderType::kSell, 5))
    os << "  " << FormatPrice(order.price) << " x " << order.shares << '\n';
  os << "--- BIDS (best to worst, up to 5) ---\n";
  for (const Order& order : book.GetTopN(OrderType::kBuy, 5))
    os << "  " << FormatPrice(order.price) << " x " << order.shares << '\n';
  os << "--- TRADES ---\n";
  for (const Trade& trade : book.trade_log_)
    os << "  " << trade.shares << " shares @ " << FormatPrice(trade.price) << " (buy #" << trade.buy_order_id << ", sell #" << trade.sell_order_id << ")\n";
  if (book.bids_.IsEmpty() || book.asks_.IsEmpty())
    os << "Spread: N/A\n";
  else
    os << "Spread: " << FormatPrice(book.GetBestAsk().price - book.GetBestBid().price) << '\n';
  return os;
}
