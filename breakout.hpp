#pragma once
#include <exception>
#include "ColorManager.hpp"
#include "EventManager.hpp"
#include "MainWindow.hpp"

/**
  @namespace breakout
  The breakout game
*/

namespace breakout {

struct DisplayException : public std::exception {
  std::string msg;
  DisplayException(std::string&& msg) : std::exception(), msg(msg) { }

  const char* what() const noexcept override {
    return msg.c_str();
  }
};

class GameState {
  bool _is_running = true;
public:
  void exit();
  bool is_running() const;
};

extern GameState game;

}
