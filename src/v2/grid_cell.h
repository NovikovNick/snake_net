#ifndef SNAKE_GRID_CELL_H_
#define SNAKE_GRID_CELL_H_
#include <iostream>

namespace snake {

enum class Direction : std::uint8_t { UP = 3, LEFT = 2, RIGHT = 1, BOTTOM = 0 };

struct GridCell final {
  uint8_t data;

  GridCell();
  GridCell(const int data);

  bool isEmpty() const;
  bool isPlayer() const;
  bool isPlayer(const uint8_t id) const;
  bool isApple() const;
  bool isNextApple() const;
  Direction getPrev() const;
  Direction getDir() const;
  uint8_t getPlayerId() const;

  void setEmpty(const bool flag);
  void setCurrApple();
  void setPrevApple();

  void setPlayer(const uint8_t id, Direction dir, Direction prev);
};
}  // namespace snake
#endif  // SNAKE_GRID_CELL_H_
