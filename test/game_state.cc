#define BOOST_TEST_MODULE SolutionTest
#define CASE_1 1
#define CASE_2 1
#define CASE_3 1
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

#if CASE_1
BOOST_AUTO_TEST_CASE(case1) {
  // arrange
  snake::GameState gs;
  gs.Init();

  // act
  print(gs);

  for (const auto& dir : {snake::Direction::BOTTOM, snake::Direction::RIGHT,
                          snake::Direction::UP, snake::Direction::LEFT}) {
    gs.Update(new int[]{static_cast<int>(dir), -1}, 0);
    for (int i = 0; i < 4; ++i) {
      gs.MoveShip(0);
      print(gs);
    }
  }

  // assert
}
#endif  // !CASE_1
