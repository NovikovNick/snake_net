#ifndef SNAKE_GAME_STATE_H_
#define SNAKE_GAME_STATE_H_
#include <iostream>

#include "grid_cell.h"

#define DEBUG 1

namespace snake {

struct Player final {
  uint8_t x, y, score;
  Player() : Player(0, 0, 0){};
  Player(const uint8_t x, const uint8_t y, const uint8_t score)
      : x(x), y(y), score(score){};
};

struct GameState final {
  const static int n = 10;
  const static int player_count = 2;

  GridCell grid[n * n];
  Player player[player_count];
  uint8_t status;
  int _framenumber;

  void MoveShip(const int player_id);
  void Init();
  void Update(int inputs[], int disconnect_flags);
};

}  // namespace snake
#endif  // SNAKE_GAME_STATE_H_
