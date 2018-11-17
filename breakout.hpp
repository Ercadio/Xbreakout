#pragma once
#include <exception>
#include "ColorManager.hpp"
#include "EventManager.hpp"
#include "MainWindow.hpp"
#include "view/view.hpp"
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
  int _pad_pos;
  int _x_ball, _y_ball;
  std::map<std::tuple<int, int>, Brick> _bricks;
public:
  GameState();
  void exit();
  bool is_running() const;
  void use_power();
  void display();
};

extern GameState game;

}
