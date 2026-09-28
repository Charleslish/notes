#include "tiles.hpp"

unsigned int TilesAcross(unsigned int width_mm, unsigned int tile_mm) {
  if (tile_mm == 0) {
    return 0;
  }

  return width_mm / tile_mm;
}

unsigned int TilesForFloor(unsigned int width_mm, unsigned int depth_mm,
                          unsigned int tile_mm) {
  return TilesAcross(width_mm, tile_mm) * TilesAcross(depth_mm, tile_mm);
}
