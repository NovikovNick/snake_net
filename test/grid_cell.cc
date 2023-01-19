#define BOOST_TEST_MODULE SolutionTest
#define CASE_1 1
#define CASE_2 1
#define CASE_3 1
#define DEBUG 1

#include "../src/v2/grid_cell.h"

#include <bitset>
#include <boost/test/included/unit_test.hpp>
#include <iostream>

#if CASE_1
BOOST_AUTO_TEST_CASE(case1) {
  // arrange
  snake::GridCell cell;

  // act && assert
  cell.setEmpty(true);
  BOOST_CHECK(cell.isEmpty());

  cell.setEmpty(false);
  BOOST_CHECK(!cell.isEmpty());

  cell.setEmpty(true);
  BOOST_CHECK(cell.isEmpty());
}
#endif  // !CASE_1

#if CASE_2
BOOST_AUTO_TEST_CASE(case2) {
  // arrange
  snake::GridCell cell;

  // act && assert

  std::cout << std::bitset<8>(cell.data) << std::endl;

  cell.setPlayer(1, snake::Direction::UP, snake::Direction::UP);
  std::cout << std::bitset<8>(cell.data) << std::endl;
  BOOST_CHECK_EQUAL(1, cell.getPlayerId());
  BOOST_CHECK(snake::Direction::UP == cell.getDir());
  BOOST_CHECK(snake::Direction::UP == cell.getPrev());

  cell.setPlayer(0, snake::Direction::LEFT, snake::Direction::LEFT);
  std::cout << std::bitset<8>(cell.data) << std::endl;
  BOOST_CHECK_EQUAL(0, cell.getPlayerId());
  BOOST_CHECK(snake::Direction::LEFT == cell.getDir());
  BOOST_CHECK(snake::Direction::LEFT == cell.getPrev());

  cell.setPlayer(1, snake::Direction::RIGHT, snake::Direction::RIGHT);
  std::cout << std::bitset<8>(cell.data) << std::endl;
  BOOST_CHECK_EQUAL(1, cell.getPlayerId());
  BOOST_CHECK(snake::Direction::RIGHT == cell.getDir());
  BOOST_CHECK(snake::Direction::RIGHT == cell.getPrev());

  cell.setPlayer(0, snake::Direction::BOTTOM, snake::Direction::BOTTOM);
  std::cout << std::bitset<8>(cell.data) << std::endl;
  BOOST_CHECK_EQUAL(0, cell.getPlayerId());
  BOOST_CHECK(snake::Direction::BOTTOM == cell.getDir());
  BOOST_CHECK(snake::Direction::BOTTOM == cell.getPrev());
}
#endif  // !CASE_2

#if CASE_3
BOOST_AUTO_TEST_CASE(case3) {
  // arrange
  snake::GridCell cell;

  // act && assert
  std::cout << std::bitset<8>(cell.data) << std::endl;
  BOOST_CHECK(cell.isNextApple());
  BOOST_CHECK(!cell.isApple());

  cell.setCurrApple();
  std::cout << std::bitset<8>(cell.data) << std::endl;
  BOOST_CHECK(cell.isApple());
  BOOST_CHECK(!cell.isNextApple());

  cell.setPrevApple();
  std::cout << std::bitset<8>(cell.data) << std::endl;
  BOOST_CHECK(!cell.isApple());
  BOOST_CHECK(!cell.isNextApple());
}
#endif  // !CASE_3