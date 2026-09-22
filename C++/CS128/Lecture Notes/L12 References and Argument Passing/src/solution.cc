#include "solution.hpp"

void PullHolds(std::vector<std::string>& shelf,
               std::vector<std::string>& hold_cart,
               const std::set<std::string>& requested) {
    std::vector<std::string> new_shelf;
    for(const auto& book : shelf){
      if(requested.contains(book))
        hold_cart.push_back(book);
      else
        new_shelf.push_back(book);
    }
    shelf = new_shelf;
}
