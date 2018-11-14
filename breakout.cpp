#include "breakout.hpp"


namespace breakout {

GameState game;

void GameState::exit() {
  _is_running = false;
}

bool GameState::is_running() const { return _is_running; }

} // namespace
