#include "inventory.hpp"

bool Inventory::AddStock(const std::string& item, int quantity){
    if(quantity <= 0 || quantity > kMaxQuantity)
        return false;
    if(!stock_.contains(item)){
        stock_[item] += quantity;
        return true;
    }
    if(stock_[item] + quantity > kMaxQuantity)
        return false;
    stock_[item] += quantity;
    return true;
}

bool Inventory::Sell(const std::string& item, int quantity){
    if(quantity <= 0 || !HasAtLeast(item, quantity))
        return false;
    stock_[item] -= quantity;
    RemoveIfEmpty(item);
    return true;
}

bool Inventory::InStock(const std::string& item) const{
    return stock_.contains(item);
}

int Inventory::GetQuantity(const std::string& item) const{
    if(!stock_.contains(item))
        return 0;
    return stock_.at(item);
}
int Inventory::GetTotalItems() const{
    if(stock_.empty())
        return 0;
    int total = 0;
    for(const auto& pair : stock_)
        total += pair.second;
    return total;
}


bool Inventory::HasAtLeast(const std::string& item, int quantity) const{
    return stock_.contains(item) && (stock_.at(item) >= quantity);
}
void Inventory::RemoveIfEmpty(const std::string& item){
    if(stock_.contains(item) && stock_.at(item) == 0)
        stock_.erase(item);
}