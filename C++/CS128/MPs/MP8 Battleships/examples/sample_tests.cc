#include "board.hpp"
#include "ship.hpp"

#include <catch2/catch_test_macros.hpp>
#include <set>

TEST_CASE("Append links segments from bow to stern", "[ship-append]") {
  Ship ship;
  Segment* bow = ship.Append(0, 0, 0);
  Segment* middle = ship.Append(0, 1, 1);
  Segment* stern = ship.Append(0, 2, 2);
  REQUIRE(ship.Bow() == bow);
  REQUIRE(ship.Stern() == stern);
  REQUIRE(ship.Length() == 3);
  REQUIRE(bow->prev == nullptr);
  REQUIRE(bow->next == middle);
  REQUIRE(middle->prev == bow);
  REQUIRE(middle->next == stern);
  REQUIRE(stern->prev == middle);
  REQUIRE(stern->next == nullptr);
  REQUIRE(ship.Center() == middle);
}

TEST_CASE("An empty board renders as water", "[board-render]") {
  const Board kBoard(2, 3);
  REQUIRE(kBoard.Render(true) == "...\n...\n");
  REQUIRE(kBoard.ShipsAfloat() == 0);
}

TEST_CASE("An off-center hit removes a segment, and a repeat changes nothing",
          "[fire]") {
  Board board(3, 6);
  board.PlaceShip('A', 1, 1, 4, Orientation::kHorizontal);

  const ShotReport kHit = board.Fire(1, 4);
  REQUIRE(kHit.target == ShotResult::kHit);
  REQUIRE(kHit.hits == std::set<Coord>{{1, 4}});
  REQUIRE(kHit.misses.empty());
  REQUIRE(kHit.sunk.empty());
  REQUIRE(board.Render(true) == "......\n.AAAX.\n......\n");

  const ShotReport kRepeat = board.Fire(1, 4);
  REQUIRE(kRepeat.target == ShotResult::kRepeat);
  REQUIRE(kRepeat.hits.empty());
  REQUIRE(kRepeat.misses.empty());
  REQUIRE(kRepeat.sunk.empty());
  REQUIRE(board.Render(true) == "......\n.AAAX.\n......\n");
}

TEST_CASE("A sinking whose detonation reaches no unfired cell", "[sink]") {
  Board board(1, 3);
  board.PlaceShip('A', 0, 0, 3, Orientation::kHorizontal);

  const ShotReport kReport = board.Fire(0, 1);
  REQUIRE(kReport.target == ShotResult::kSunk);
  REQUIRE(kReport.hits == std::set<Coord>{{0, 1}});
  REQUIRE(kReport.misses.empty());
  REQUIRE(kReport.sunk == std::set<char>{'A'});
  REQUIRE(board.IsSunk('A'));
  REQUIRE(board.StateAt(0, 0) == CellState::kHit);
  REQUIRE(board.StateAt(0, 2) == CellState::kHit);
  REQUIRE(board.Render(false) == "aaa\n");
}

TEST_CASE("The chain reaction of Figure 12", "[chain]") {
  Board board(7, 7);
  board.PlaceShip('D', 0, 0, 4, Orientation::kVertical);
  board.PlaceShip('A', 0, 2, 3, Orientation::kVertical);
  board.PlaceShip('B', 2, 4, 3, Orientation::kVertical);
  board.PlaceShip('C', 5, 0, 2, Orientation::kVertical);

  const ShotReport kReport = board.Fire(1, 2);
  REQUIRE(kReport.target == ShotResult::kSunk);
  REQUIRE(kReport.hits ==
          std::set<Coord>{{0, 0}, {1, 0}, {1, 2}, {2, 0}, {2, 4}, {5, 0}});
  REQUIRE(kReport.misses.size() == 18);
  REQUIRE(kReport.sunk == std::set<char>{'A', 'C', 'D'});
  REQUIRE(board.ShipsAfloat() == 1);
}

TEST_CASE("A ship whose center a wave misses loses its segments and stays afloat",
          "[wave]") {
  Board board(7, 7);
  board.PlaceShip('A', 0, 2, 3, Orientation::kHorizontal);
  board.PlaceShip('B', 5, 2, 4, Orientation::kHorizontal);
  board.PlaceShip('C', 2, 4, 2, Orientation::kVertical);
  board.PlaceShip('D', 2, 2, 2, Orientation::kVertical);

  const ShotReport kReport = board.Fire(0, 3);
  REQUIRE(kReport.target == ShotResult::kSunk);
  REQUIRE(kReport.hits ==
          std::set<Coord>{{0, 3}, {2, 2}, {2, 4}, {5, 2}, {5, 4}});
  REQUIRE(kReport.misses.size() == 24);
  REQUIRE(kReport.sunk == std::set<char>{'A', 'C', 'D'});
  REQUIRE_FALSE(board.IsSunk('B'));
  REQUIRE(board.StateAt(5, 3) == CellState::kUnfired);
  REQUIRE(board.StateAt(5, 5) == CellState::kUnfired);
}
