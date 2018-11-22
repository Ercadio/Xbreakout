#include "breakout.hpp"


namespace breakout {

GameState game;

void GameState::exit() {
  _is_running = false;
}

bool GameState::is_running() const { return _is_running; }

void GameState::use_power() { std::cout << "[INFO] Used a power!" << std::endl; }

void GameState::display() { }

GameState::GameState() {
  // This is demo code until we implement level loaders
  // Create an 8x4 brick wall
  for(int i = 0; i < 8; ++i) {
    for(int j = 0; j < 4; ++j) {
      _bricks[std::make_tuple(i, j)] = Brick(); 
    }
  }
}

} // namespace
