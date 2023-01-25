#define BOOST_TEST_MODULE SolutionTest
#define CASE_1 1
#define CASE_2 1
#define CASE_3 1
#define CASE_4 1
#define CASE_5 1
#define DEBUG 1

#include "../src/v2/game_state.h"

#include <bitset>
#include <boost/test/included/unit_test.hpp>
#include <iostream>

#include "../src/util/log.h"

void print(const snake::GameState& gs) {
  util::debug("-------------------\n");
  int n = snake::GameState::n;
  for (int i = 0; i < n * n; ++i) {
    // std::cout << std::bitset<8>(gs.grid[i].data) << " ";
    auto sign = "";
    sign = gs.grid[i].isEmpty() ? "+" : sign;
    sign = gs.grid[i].isPlayer() ? gs.grid[i].isPlayer(1) ? "0" : "1" : sign;
    sign = gs.grid[i].isApple() ? "A" : sign;
    util::debug("{} ", sign);
    if ((i % n) == (n - 1)) util::debug("\n");
  }
};

void assertGrid(const snake::GameState& gs,
                const std::vector<std::pair<int, int>>& p0,
                const std::vector<std::pair<int, int>>& p1,
                const std::pair<int, int> apple) {
  std::vector<char> expected_grid(gs.n * gs.n, ' ');
  for (const auto [x, y] : p0) expected_grid[gs.n * y + x] = '0';
  for (const auto [x, y] : p1) expected_grid[gs.n * y + x] = '1';
  expected_grid[gs.n * apple.second + apple.first] = 'a';

  for (int i = 0; i < gs.n * gs.n; ++i) {
    int row = i / gs.n;
    int col = i % gs.n;
    switch (expected_grid[i]) {
      case '0':
        BOOST_TEST_INFO(std::format("expected player 0 at[{}, {}]", col, row));
        BOOST_CHECK(gs.grid[i].isPlayer() && gs.grid[i].isPlayer(0));
        break;
      case '1':
        BOOST_TEST_INFO(std::format("expected player 1 at[{}, {}]", col, row));
        BOOST_CHECK(gs.grid[i].isPlayer() && gs.grid[i].isPlayer(1));
        break;
      case 'a':
        BOOST_TEST_INFO(std::format("expected an apple at[{}, {}]", col, row));
        BOOST_CHECK(gs.grid[i].isApple());
        break;
      default:
        BOOST_TEST_INFO(std::format("expected empty at[{}, {}]", col, row));
        BOOST_CHECK(gs.grid[i].isEmpty());
        break;
    }
  }
};

#if CASE_1
BOOST_AUTO_TEST_CASE(case1) {
  // arrange
  snake::GameState gs;
  // act
  gs.Init();
  // assert
  print(gs);
  assertGrid(gs,  
      {{1, 1}, {2, 1}, {3, 1}, {4, 1}}, 
      {{1, 9}, {2, 9}, {3, 9}, {4, 9}},
      {8, 8});
}
#endif  // !CASE_1

#if CASE_2
BOOST_AUTO_TEST_CASE(case2) {
  // arrange
  snake::GameState gs;
  gs.Init();
  // act
  gs.Update(new int[]{static_cast<int>(snake::Direction::BOTTOM), -1}, 0);
  gs.MoveShip(0);

  // assert
  print(gs);
  assertGrid(gs, 
      {{2, 1}, {3, 1}, {4, 1}, {4, 2}},
      {{1, 9}, {2, 9}, {3, 9}, {4, 9}},
      {8, 8});
}
#endif  // !CASE_2

#if CASE_3
BOOST_AUTO_TEST_CASE(case3) {
  // arrange
  snake::GameState gs;
  gs.Init();
  // act
  gs.Update(new int[]{static_cast<int>(snake::Direction::UP), -1}, 0);
  gs.MoveShip(0);

  // assert
  print(gs);
  assertGrid(gs, 
      {{2, 1}, {3, 1}, {4, 1}, {4, 0}},
      {{1, 9}, {2, 9}, {3, 9}, {4, 9}}, 
      {8, 8});
}
#endif  // !CASE_3

#if CASE_4
BOOST_AUTO_TEST_CASE(case4) {
  // arrange
  snake::GameState gs;
  gs.Init();
  // act
  gs.Update(new int[]{static_cast<int>(snake::Direction::BOTTOM), -1}, 0);
  gs.MoveShip(0);
  gs.MoveShip(0);
  gs.MoveShip(0);
  gs.MoveShip(0);
  gs.Update(new int[]{static_cast<int>(snake::Direction::RIGHT), -1}, 0);
  gs.MoveShip(0);
  gs.MoveShip(0);
  gs.MoveShip(0);

  // assert
  print(gs);
  assertGrid(gs, 
      {{4, 5}, {5, 5}, {6, 5}, {7, 5}},
      {{1, 9}, {2, 9}, {3, 9}, {4, 9}}, 
      {8, 8});
}
#endif  // !CASE_4


#if CASE_5
BOOST_AUTO_TEST_CASE(case5) {
  // arrange
  snake::GameState gs;
  gs.Init();
  // act
  gs.Update(new int[]{static_cast<int>(snake::Direction::BOTTOM), -1}, 0);
  gs.MoveShip(0);
  gs.MoveShip(0);
  gs.MoveShip(0);
  gs.MoveShip(0);
  gs.Update(new int[]{static_cast<int>(snake::Direction::LEFT), -1}, 0);
  gs.MoveShip(0);
  gs.MoveShip(0);
  gs.MoveShip(0);

  // assert
  print(gs);
  assertGrid(gs, 
      {{1, 5}, {2, 5}, {3, 5}, {4, 5}},
      {{1, 9}, {2, 9}, {3, 9}, {4, 9}},
      {8, 8});
}
#endif  // !CASE_5
