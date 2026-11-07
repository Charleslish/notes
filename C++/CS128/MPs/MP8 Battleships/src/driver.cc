#include <iostream>

#include "board.hpp"

int main() {
  Board board(5, 6);
  board.PlaceShip('A', 2, 0, 3, Orientation::kHorizontal);
  std::cout << board.Render(true) << '\n';
  ShotReport report = board.Fire(2, 1);
  std::cout << "hits " << report.hits.size() << ", misses "
            << report.misses.size() << ", sunk " << report.sunk.size()
            << "\n\n";
  std::cout << board.Render(true);
}
