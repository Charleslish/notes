#include <iostream>

#include "tiles.hpp"

int main() {
  const unsigned int kWidthMm = 3600;
  const unsigned int kDepthMm = 2400;
  const unsigned int kTileMm = 300;

  std::cout << "Tiles across: " << TilesAcross(kWidthMm, kTileMm) << std::endl;
  std::cout << "Tiles for the floor: "
            << TilesForFloor(kWidthMm, kDepthMm, kTileMm) << std::endl;

  return 0;
}
