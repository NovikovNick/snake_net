#include "game_state.h"

#include "../util/log.h"
namespace {
const static int n = snake::GameState::n;

snake::GridCell& getGridCell(snake::GridCell grid[], const int x, const int y) {
  return grid[snake::GameState::n * y + x];
};

std::pair<int, int> move(const int x, const int y, snake::Direction dir) {
  const int n = snake::GameState::n;
  switch (dir) {
    case snake::Direction::UP:
      return (y - 1 < 0) ? std::make_pair(x, n - 1) : std::make_pair(x, y - 1);
    case snake::Direction::BOTTOM:
      return (y + 1 >= n) ? std::make_pair(x, 0) : std::make_pair(x, y + 1);
    case snake::Direction::LEFT:
      return (x - 1 < 0) ? std::make_pair(n - 1, y) : std::make_pair(x - 1, y);
    case snake::Direction::RIGHT:
      return (x + 1 >= n) ? std::make_pair(0, y) : std::make_pair(x + 1, y);
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

void GameState::MoveShip(const int player_id) {
  _framenumber++;
  auto head_x = player[player_id].x;
  auto head_y = player[player_id].y;
  const auto head = getGridCell(grid, head_x, head_y);

  auto [next_head_x, next_head_y] = move(head_x, head_y, head.getDir());
  auto& next_head = getGridCell(grid, next_head_x, next_head_y);
  next_head.setPlayer(player_id, head.getDir(), apposite(head.getDir()));

  if (next_head.isApple()) {
    next_head.setPrevApple();
  } else {
    auto [tail_x, tail_y] = getTail(grid, player_id, head_x, head_y);
    getGridCell(grid, tail_x, tail_y).setEmpty(true);
  }

  player[player_id].x = next_head_x;
  player[player_id].y = next_head_y;
}

void GameState::Init() {
  _framenumber = 0;
  memset(grid, GridCell{}.data, sizeof(grid));

  player[0] = Player(4, 1, 0);
  player[1] = Player(4, 9, 0);
  for (int i = 1; i <= 4; ++i) {
    getGridCell(grid, i, 1).setPlayer(0, Direction::RIGHT, Direction::LEFT);
    getGridCell(grid, i, 9).setPlayer(1, Direction::RIGHT, Direction::LEFT);
  }
  getGridCell(grid, 8, 8).setCurrApple();
  status = 0;
}

void GameState::Update(int inputs[], int disconnect_flags) {
  for (int player_id = 0; player_id <= GameState::player_count; ++player_id) {
    if (inputs[player_id] != -1) {
      auto& head = getGridCell(grid, player[player_id].x, player[player_id].y);
      auto dir = static_cast<Direction>(inputs[player_id]);
      head.setPlayer(player_id, dir, head.getPrev());
    }
  }
}
}  // namespace snake