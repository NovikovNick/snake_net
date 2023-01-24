#include "game_state.h"

#include "../util/log.h"
namespace {
const static int n = snake::GameState::n;

snake::GridCell& getGridCell(snake::GridCell grid[], const int x, const int y) {
  return grid[snake::GameState::n * y + x];
};

std::pair<int, int> move(const int x, const int y, snake::Direction dir) {
  switch (dir) {
    case snake::Direction::UP:
      return {x, y - 1};
    case snake::Direction::BOTTOM:
      return {x, y + 1};
    case snake::Direction::LEFT:
      return {x - 1, y};
    case snake::Direction::RIGHT:
      return {x + 1, y};
    default:
      throw std::invalid_argument("no such direction");
  }
}

snake::Direction apposite(snake::Direction dir) {
  switch (dir) {
    case snake::Direction::UP:
      return snake::Direction::BOTTOM;
    case snake::Direction::BOTTOM:
      return snake::Direction::UP;
    case snake::Direction::LEFT:
      return snake::Direction::RIGHT;
    case snake::Direction::RIGHT:
      return snake::Direction::LEFT;
    default:
      throw std::invalid_argument("no such direction");
  }
}

}  // namespace

namespace snake {

void GameState::MoveShip(int i) {
  auto& player = i == 0 ? p1 : p2;
  auto& head = getGridCell(grid, player.x, player.y);
  auto head_dir = head.getDir();
  auto apposite_head_dir = apposite(head.getDir());

  auto [x, y] = move(player.x, player.y, head_dir);
  auto isHeadEmpty = head.isEmpty();
  auto& next_head = getGridCell(grid, x, y);
  next_head.setPlayer(i, head_dir, apposite_head_dir);

  auto [tail_x, tail_y] = move(player.x, player.y, head.getPrev());
  auto prev_x = tail_x;
  auto prev_y = tail_y;
  while (getGridCell(grid, tail_x, tail_y).isPlayer(i)) {
    prev_x = tail_x;
    prev_y = tail_y;
    auto prev_dir = getGridCell(grid, tail_x, tail_y).getPrev();
    auto coord = move(tail_x, tail_y, prev_dir);
    tail_x = coord.first;
    tail_y = coord.second;
  }
  if (next_head.isApple()) {
    next_head.setPrevApple();
  } else {
    getGridCell(grid, prev_x, prev_y).setEmpty(true);
  }

  player.x = x;
  player.y = y;
}

void GameState::Init() {
  memset(grid, 1, sizeof(grid));

  p1 = Player(4, 1, 0);
  p2 = Player(4, 9, 0);
  for (int i = 1; i <= 4; ++i) {
    getGridCell(grid, i, 1).setPlayer(0, Direction::RIGHT, Direction::LEFT);
    getGridCell(grid, i, 9).setPlayer(1, Direction::RIGHT, Direction::LEFT);
  }
  getGridCell(grid, 8, 8).setCurrApple();
  status = 0;
}

void GameState::Update(int inputs[], int disconnect_flags) {
  if (inputs[0] != -1) {
    auto& head = getGridCell(grid, p1.x, p1.y);
    head.setPlayer(0, static_cast<Direction>(inputs[0]), head.getPrev());
  }

  if (inputs[1] != -1) {
    auto& head = getGridCell(grid, p2.x, p2.y);
    head.setPlayer(1, static_cast<Direction>(inputs[1]), head.getPrev());
  }
}

}  // namespace snake