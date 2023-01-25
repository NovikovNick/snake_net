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

std::pair<int, int> getTail(snake::GridCell grid[], const int player_id,
                            const int head_x, const int head_y) {
  std::pair<int, int> tail_coord, curr_coord = {head_x, head_y};
  snake::GridCell curr = getGridCell(grid, head_x, head_y);
  while (curr.isPlayer(player_id)) {
    tail_coord = curr_coord;
    curr_coord = move(curr_coord.first, curr_coord.second, curr.getPrev());
    curr = getGridCell(grid, curr_coord.first, curr_coord.second);
  }
  return tail_coord;
}

}  // namespace

namespace snake {

void GameState::MoveShip(int player_id) {
  auto& player = player_id == 0 ? p1 : p2;
  const auto head = getGridCell(grid, player.x, player.y);

  auto [next_head_x, next_head_y] = move(player.x, player.y, head.getDir());
  auto& next_head = getGridCell(grid, next_head_x, next_head_y);
  next_head.setPlayer(player_id, head.getDir(), apposite(head.getDir()));
  
  if (next_head.isApple()) {
    next_head.setPrevApple();
  } else {
    auto [tail_x, tail_y] = getTail(grid, player_id, player.x, player.y);
    getGridCell(grid, tail_x, tail_y).setEmpty(true);
  }

  player.x = next_head_x;
  player.y = next_head_y;
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