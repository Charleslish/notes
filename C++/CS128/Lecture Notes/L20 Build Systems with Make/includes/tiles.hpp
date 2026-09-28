#ifndef TILES_HPP
#define TILES_HPP

unsigned int TilesAcross(unsigned int width_mm, unsigned int tile_mm);
unsigned int TilesForFloor(unsigned int width_mm, unsigned int depth_mm,
                          unsigned int tile_mm);

#endif  // TILES_HPP
