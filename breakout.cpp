#include "breakout.hpp"


namespace breakout {

GameState game;

void GameState::exit() {
  _is_running = false;
}

bool GameState::is_running() const { return _is_running; }

void GameState::use_power() { std::cout << "[INFO] Used a power!" << std::endl; }

void GameState::display() { }

} // namespace
