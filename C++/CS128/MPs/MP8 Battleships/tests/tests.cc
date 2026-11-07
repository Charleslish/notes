#include <catch2/catch_test_macros.hpp>

#include "board.hpp"
#include "ship.hpp"

TEST_CASE("A new ship is empty", "[ship-empty]") {
  const Ship kShip;
  REQUIRE(kShip.Bow() == nullptr);
  REQUIRE(kShip.Stern() == nullptr);
  REQUIRE(kShip.Center() == nullptr);
  REQUIRE(kShip.Length() == 0);
  REQUIRE(kShip.IsSunk());
}
#include "board.hpp"
#include "ship.hpp"

#include <catch2/catch_test_macros.hpp>
#include <set>
#include <stdexcept>

TEST_CASE("Ship removal updates the ends and insertion restores order", "[ship]") {
  Ship ship;
  Segment* first = ship.Append(0, 0, 0);
  Segment* middle = ship.Append(0, 1, 1);
  Segment* last = ship.Append(0, 2, 2);
  ship.Remove(middle);
  REQUIRE(first->next == last);
  REQUIRE(last->prev == first);
  Segment* restored = ship.InsertInOrder(0, 1, 1);
  REQUIRE(first->next == restored);
  REQUIRE(restored->prev == first);
  REQUIRE(restored->next == last);
  REQUIRE(last->prev == restored);
  REQUIRE(ship.Center() == restored);
}

TEST_CASE("Ship copies own independent linked lists", "[ship-copy]") {
  Ship source;
  Segment* first = source.Append(1, 1, 0);
  source.Append(1, 3, 2);
  Ship copy(source);
  REQUIRE(copy.Bow() != first);
  REQUIRE(copy.Bow()->row == first->row);
  REQUIRE(copy.Bow()->next->original_index == 2);
  copy.Remove(copy.Bow());
  REQUIRE(source.Length() == 2);
  Ship assigned;
  assigned = source;
  Ship& same_ship = assigned;
  assigned = same_ship;
  REQUIRE(assigned.Length() == 2);
  REQUIRE(assigned.Bow() != source.Bow());
}

TEST_CASE("Placement supports all orientations and rejects edge contact", "[placement]") {
  Board horizontal(1, 3);
  Board vertical(3, 1);
  Board down_right(3, 3);
  Board down_left(3, 3);
  horizontal.PlaceShip('A', 0, 0, 3, Orientation::kHorizontal);
  vertical.PlaceShip('B', 0, 0, 3, Orientation::kVertical);
  down_right.PlaceShip('C', 0, 0, 3, Orientation::kDiagonalDownRight);
  down_left.PlaceShip('D', 0, 2, 3, Orientation::kDiagonalDownLeft);
  const std::string before = horizontal.Render(true);
  REQUIRE_THROWS_AS(horizontal.PlaceShip('E', 0, 0, 2, Orientation::kHorizontal),
                    std::invalid_argument);
  REQUIRE(horizontal.Render(true) == before);
  REQUIRE_THROWS_AS(horizontal.PlaceShip('E', 0, 0, 2, Orientation::kVertical),
                    std::invalid_argument);
}

TEST_CASE("Repair reinserts a removed segment and updates the center", "[repair]") {
  Board board(3, 6);
  board.PlaceShip('A', 1, 1, 4, Orientation::kHorizontal);
  board.Fire(1, 4);
  board.Fire(1, 3);
  board.Fire(1, 2);
  board.Repair(1, 3);
  board.Repair(1, 4);
  board.Repair(1, 2);
  REQUIRE(board.StateAt(1, 2) == CellState::kUnfired);
  REQUIRE(board.Fire(1, 2).target == ShotResult::kSunk);
  REQUIRE(board.IsSunk('A'));
}

TEST_CASE("Board copies keep independent storage after source changes", "[board-copy]") {
  Board source(4, 5);
  source.PlaceShip('A', 1, 0, 3, Orientation::kHorizontal);
  source.Fire(1, 2);
  Board copy(source);
  REQUIRE(copy.Render(true) == source.Render(true));
  source.Repair(1, 2);
  REQUIRE(copy.StateAt(1, 2) == CellState::kHit);
  Board assigned(1, 1);
  assigned = copy;
  REQUIRE(assigned.Render(true) == copy.Render(true));
  Board& same_board = assigned;
  assigned = same_board;
  REQUIRE(assigned.Render(true) == copy.Render(true));
}
