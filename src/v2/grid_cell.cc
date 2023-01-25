#include "grid_cell.h"

#include <bitset>

namespace {

uint8_t dir_msk = 0b11000000;
uint8_t prev_mask = 0b00110000;
uint8_t player_id_mask = 0b00001000;
uint8_t apple_mask = 0b00000110;
uint8_t curr_apple = (3 << 1);
uint8_t prev_apple = (2 << 1);

int empty_b = 0b00000001;

}  // namespace

namespace snake {

GridCell::GridCell(const int data) : data(data){};

GridCell::GridCell() : GridCell(0) { setEmpty(true); };

bool GridCell::isEmpty() const { return data & empty_b; }

void GridCell::setEmpty(const bool flag) {
  std::bitset<8> set(data);
  set[0] = flag;
  data = set.to_ullong();
}

bool GridCell::isPlayer() const { return !isEmpty() && !isApple(); }

bool GridCell::isPlayer(const uint8_t id) const {
  auto playerid = std::bitset<8>(data)[3];
  return isPlayer() && (id == std::bitset<8>(data)[3]);
}

bool GridCell::isApple() const { return (data & apple_mask) == curr_apple; }

bool GridCell::isNextApple() const { return (data & apple_mask) == 0; }

void GridCell::setCurrApple() {
  setEmpty(false);
  std::bitset<8> set(data);
  set[1] = set[2] = 0;
  data = set.to_ullong();
  data |= curr_apple;
}

void GridCell::setPrevApple() {
  std::bitset<8> set(data);
  set[1] = set[2] = 0;
  data = set.to_ullong();
  data |= prev_apple;
}

uint8_t GridCell::getPlayerId() const {
  return ((data & player_id_mask) == player_id_mask) ? 1 : 0;
}

Direction GridCell::getPrev() const {
  return static_cast<Direction>((data & prev_mask) >> 4);
}

Direction GridCell::getDir() const {
  return static_cast<Direction>((data & dir_msk) >> 6);
}

void GridCell::setPlayer(const uint8_t id, Direction dir, Direction prev) {
  setEmpty(false);

  std::bitset<8> set(data);
  set[3] = set[4] = set[5] = set[6] = set[7] = 0;
  data = set.to_ullong();

  if (id) data |= player_id_mask;
  data |= (static_cast<int>(dir) << 6);
  data |= (static_cast<int>(prev) << 4);
};

}  // namespace snake