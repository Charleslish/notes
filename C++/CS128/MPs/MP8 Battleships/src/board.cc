#include "board.hpp"

#include <cctype>
#include <stdexcept>

Board::Board(unsigned int rows, unsigned int cols) : rows_(rows), cols_(cols) {
  if (rows == 0 || cols == 0)
    throw std::invalid_argument("board dimensions must be positive");
  cells_ = new Cell*[rows_];
  for (unsigned int row = 0; row < rows_; ++row)
    cells_[row] = new Cell[cols_];
}

Board::Board(const Board& other) {
  CopyFrom(other);
}

Board& Board::operator=(const Board& other) {
  if (this == &other)
    return *this;
  Release();
  CopyFrom(other);
  return *this;
}

Board::~Board() {
  Release();
}

bool Board::InBounds(unsigned int row, unsigned int col) const {
  return row < rows_ && col < cols_;
}

bool Board::Fits(unsigned int row, unsigned int col, unsigned int length,
                 Orientation orientation) const {
  if (length == 0 || !InBounds(row, col))
    return false;
  if (orientation == Orientation::kHorizontal)
    return length <= cols_ - col;
  if (orientation == Orientation::kVertical)
    return length <= rows_ - row;
  if (orientation == Orientation::kDiagonalDownRight)
    return length <= rows_ - row && length <= cols_ - col;
  if (orientation == Orientation::kDiagonalDownLeft)
    return length <= rows_ - row && length - 1 <= col;
  return false;
}

Coord Board::ShipCellAt(unsigned int row, unsigned int col, unsigned int index,
                        Orientation orientation) const {
  if (orientation == Orientation::kHorizontal)
    col += index;
  else
    row += index;
  if (orientation == Orientation::kDiagonalDownRight)
    col += index;
  if (orientation == Orientation::kDiagonalDownLeft)
    col -= index;
  return {row, col};
}

std::vector<Coord> Board::ShipCells(unsigned int row, unsigned int col,
                                    unsigned int length,
                                    Orientation orientation) const {
  std::vector<Coord> coordinates;
  if (!Fits(row, col, length, orientation))
    return coordinates;
  for (unsigned int i = 0; i < length; ++i)
    coordinates.push_back(ShipCellAt(row, col, i, orientation));
  return coordinates;
}

bool Board::CanPlace(const std::vector<Coord>& coordinates) const {
  if (coordinates.empty())
    return false;
  for (Coord coordinate : coordinates) {
    Cell& cell = cells_[coordinate.row][coordinate.col];
    if (cell.ship != '.' || cell.state != CellState::kUnfired)
      return false;
    if (coordinate.row > 0 && cells_[coordinate.row - 1][coordinate.col].ship != '.')
      return false;
    if (coordinate.row + 1 < rows_ &&
        cells_[coordinate.row + 1][coordinate.col].ship != '.')
      return false;
    if (coordinate.col > 0 && cells_[coordinate.row][coordinate.col - 1].ship != '.')
      return false;
    if (coordinate.col + 1 < cols_ &&
        cells_[coordinate.row][coordinate.col + 1].ship != '.')
      return false;
  }
  return true;
}

void Board::PlaceShip(char id, unsigned int row, unsigned int col,
                      unsigned int length, Orientation orientation) {
  if (!std::isupper(static_cast<unsigned char>(id)) || fleet_.contains(id) ||
      length == 0)
    throw std::invalid_argument("invalid ship identity or length");
  std::vector<Coord> coordinates = ShipCells(row, col, length, orientation);
  if (!CanPlace(coordinates))
    throw std::invalid_argument("invalid ship placement");
  Ship* ship = new Ship;
  for (unsigned int i = 0; i < length; ++i) {
    Coord coordinate = coordinates[i];
    Segment* segment = ship->Append(coordinate.row, coordinate.col, i);
    Cell& cell = cells_[coordinate.row][coordinate.col];
    cell.ship = id;
    cell.original_index = i;
    cell.segment = segment;
  }
  fleet_[id] = ship;
}

std::set<char> Board::ShipsToSink(const std::set<Coord>& wave) const {
  std::set<char> sinking;
  for (Coord coordinate : wave) {
    Cell& cell = cells_[coordinate.row][coordinate.col];
    if (cell.state != CellState::kUnfired || cell.ship == '.' ||
        cell.segment == nullptr)
      continue;
    if (fleet_.at(cell.ship)->Center() == cell.segment)
      sinking.insert(cell.ship);
  }
  return sinking;
}

void Board::FireCell(Coord coordinate, const std::set<char>& sinking,
                     ShotReport& report) {
  Cell& cell = cells_[coordinate.row][coordinate.col];
  if (cell.state != CellState::kUnfired)
    return;
  cell.state = cell.ship == '.' ? CellState::kMiss : CellState::kHit;
  if (cell.ship == '.') {
    report.misses.insert(coordinate);
    return;
  }
  report.hits.insert(coordinate);
  if (!sinking.contains(cell.ship)) {
    Segment* segment = cell.segment;
    cell.segment = nullptr;
    fleet_.at(cell.ship)->Remove(segment);
  }
}

std::set<Coord> Board::SinkWave(const std::set<char>& sinking,
                                ShotReport& report) {
  std::set<Coord> next_wave;
  for (char id : sinking) {
    Sink(id);
    report.sunk.insert(id);
    std::set<Coord> blast = BlastCells(id);
    next_wave.insert(blast.begin(), blast.end());
  }
  return next_wave;
}

ShotReport Board::Fire(unsigned int row, unsigned int col) {
  if (!InBounds(row, col))
    throw std::out_of_range("shot is outside the board");
  ShotReport report;
  Cell& target = cells_[row][col];
  if (target.state != CellState::kUnfired)
    return report;
  if (target.ship == '.')
    report.target = ShotResult::kMiss;
  else if (fleet_.at(target.ship)->Center() == target.segment)
    report.target = ShotResult::kSunk;
  else
    report.target = ShotResult::kHit;
  std::set<Coord> wave{{row, col}};
  while (!wave.empty()) {
    std::set<char> sinking = ShipsToSink(wave);
    for (Coord coordinate : wave)
      FireCell(coordinate, sinking, report);
    wave = SinkWave(sinking, report);
  }
  return report;
}

void Board::Repair(unsigned int row, unsigned int col) {
  if (!InBounds(row, col))
    throw std::out_of_range("repair is outside the board");
  Cell& cell = cells_[row][col];
  if (cell.ship == '.' || cell.state != CellState::kHit ||
      fleet_.at(cell.ship)->IsSunk())
    throw std::invalid_argument("cell cannot be repaired");
  cell.segment = fleet_.at(cell.ship)->InsertInOrder(row, col, cell.original_index);
  cell.state = CellState::kUnfired;
}

unsigned int Board::ShipsAfloat() const {
  unsigned int afloat = 0;
  for (const auto& [id, ship] : fleet_)
    if (!ship->IsSunk())
      ++afloat;
  return afloat;
}

bool Board::IsSunk(char id) const {
  if (!fleet_.contains(id))
    throw std::invalid_argument("unknown ship");
  return fleet_.at(id)->IsSunk();
}

CellState Board::StateAt(unsigned int row, unsigned int col) const {
  if (!InBounds(row, col))
    throw std::out_of_range("cell is outside the board");
  return cells_[row][col].state;
}

char Board::ShipAt(unsigned int row, unsigned int col) const {
  if (!InBounds(row, col))
    throw std::out_of_range("cell is outside the board");
  return cells_[row][col].ship;
}

std::string Board::Render(bool reveal) const {
  std::string result;
  for (unsigned int row = 0; row < rows_; ++row) {
    for (unsigned int col = 0; col < cols_; ++col) {
      const Cell& cell = cells_[row][col];
      char value = '.';
      if (cell.ship != '.' && fleet_.at(cell.ship)->IsSunk())
        value = static_cast<char>(std::tolower(static_cast<unsigned char>(cell.ship)));
      else if (cell.state == CellState::kMiss)
        value = 'o';
      else if (cell.state == CellState::kHit)
        value = 'X';
      else if (reveal && cell.ship != '.')
        value = cell.ship;
      result.push_back(value);
    }
    result.push_back('\n');
  }
  return result;
}

std::set<Coord> Board::BlastCells(char id) const {
  std::set<Coord> blast;
  for (unsigned int row = 0; row < rows_; ++row)
    for (unsigned int col = 0; col < cols_; ++col)
      AddBlastForCell(blast, row, col, id);
  return blast;
}

bool Board::WithinBlastRange(unsigned int row, unsigned int col,
                             unsigned int ship_row, unsigned int ship_col,
                             char id) const {
  unsigned int row_distance = row > ship_row ? row - ship_row : ship_row - row;
  unsigned int col_distance = col > ship_col ? col - ship_col : ship_col - col;
  return cells_[ship_row][ship_col].ship == id && row_distance + col_distance <= 2;
}

void Board::AddBlastForCell(std::set<Coord>& blast, unsigned int row,
                            unsigned int col, char id) const {
  if (cells_[row][col].state != CellState::kUnfired)
    return;
  for (unsigned int ship_row = 0; ship_row < rows_; ++ship_row)
    for (unsigned int ship_col = 0; ship_col < cols_; ++ship_col)
      if (WithinBlastRange(row, col, ship_row, ship_col, id))
        blast.insert({row, col});
}

void Board::Sink(char id) {
  Ship* ship = fleet_.at(id);
  for (Segment* current = ship->Bow(); current != nullptr; current = current->next)
    cells_[current->row][current->col].segment = nullptr;
  ship->Clear();
  for (unsigned int row = 0; row < rows_; ++row)
    for (unsigned int col = 0; col < cols_; ++col)
      if (cells_[row][col].ship == id)
        cells_[row][col].state = CellState::kHit;
}

void Board::Release() {
  for (auto& [id, ship] : fleet_)
    delete ship;
  fleet_.clear();
  if (cells_ != nullptr) {
    for (unsigned int row = 0; row < rows_; ++row)
      delete[] cells_[row];
    delete[] cells_;
  }
  cells_ = nullptr;
  rows_ = 0;
  cols_ = 0;
}

void Board::CopyFrom(const Board& other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  cells_ = new Cell*[rows_];
  for (unsigned int row = 0; row < rows_; ++row) {
    cells_[row] = new Cell[cols_];
    for (unsigned int col = 0; col < cols_; ++col) {
      cells_[row][col] = other.cells_[row][col];
      cells_[row][col].segment = nullptr;
    }
  }
  for (const auto& [id, other_ship] : other.fleet_) {
    Ship* ship = new Ship(*other_ship);
    fleet_[id] = ship;
    for (Segment* current = ship->Bow(); current != nullptr; current = current->next)
      cells_[current->row][current->col].segment = current;
  }
}
