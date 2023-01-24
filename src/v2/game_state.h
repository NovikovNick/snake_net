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

  GridCell grid[n * n];
  Player p1;
  Player p2;
  uint8_t status;

  /*
  void GetShipAI(int i, double *heading, double *thrust, int *fire);
  void ParseShipInputs(int inputs, int i, double *heading, double *thrust, int
  *fire); 
  */
  void MoveShip(int i);
  void Init();
  void Update(int inputs[], int disconnect_flags);
};

}  // namespace snake
#endif  // SNAKE_GAME_STATE_H_
