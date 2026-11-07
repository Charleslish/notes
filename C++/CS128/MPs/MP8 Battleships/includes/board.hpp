#ifndef BOARD_HPP
#define BOARD_HPP

#include <map>
#include <set>
#include <string>
#include <vector>

#include "ship.hpp"
#include "utilities.hpp"

class Board {
 public:
  Board(unsigned int rows, unsigned int cols);
  Board(const Board& other);
  Board& operator=(const Board& other);
  ~Board();

  void PlaceShip(char id,
                 unsigned int row,
                 unsigned int col,
                 unsigned int length,
                 Orientation orientation);
  ShotReport Fire(unsigned int row, unsigned int col);
  void Repair(unsigned int row, unsigned int col);

  unsigned int ShipsAfloat() const;
  bool IsSunk(char id) const;
  CellState StateAt(unsigned int row, unsigned int col) const;
  char ShipAt(unsigned int row, unsigned int col) const;
  std::string Render(bool reveal) const;

 private:
  Cell** cells_ = nullptr;
  unsigned int rows_ = 0;
  unsigned int cols_ = 0;
  std::map<char, Ship*> fleet_;

  std::set<Coord> BlastCells(char id) const;
  void Sink(char id);
  void Release();
  void CopyFrom(const Board& other);
  bool InBounds(unsigned int row, unsigned int col) const;
  bool Fits(unsigned int row, unsigned int col, unsigned int length,
            Orientation orientation) const;
  Coord ShipCellAt(unsigned int row, unsigned int col, unsigned int index,
                   Orientation orientation) const;
  bool WithinBlastRange(unsigned int row, unsigned int col, unsigned int ship_row,
                        unsigned int ship_col, char id) const;
  void AddBlastForCell(std::set<Coord>& blast, unsigned int row,
                       unsigned int col, char id) const;
  std::vector<Coord> ShipCells(unsigned int row, unsigned int col,
                               unsigned int length, Orientation orientation) const;
  bool CanPlace(const std::vector<Coord>& coordinates) const;
  std::set<char> ShipsToSink(const std::set<Coord>& wave) const;
  void FireCell(Coord coordinate, const std::set<char>& sinking,
                ShotReport& report);
  std::set<Coord> SinkWave(const std::set<char>& sinking, ShotReport& report);
};

#endif
