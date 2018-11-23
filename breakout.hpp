#pragma once
#include <exception>
#include <map>

#include "ColorManager.hpp"
#include "EventManager.hpp"
#include "MainWindow.hpp"
#include "view/view.hpp"
#include "physics/physics.hpp"

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

enum PowerType { NONE, DOUBLEBALLS, LONGERPAD };

struct Brick {
  enum BrickType { NONE, DOUBLEBALLS, LONGERPAD, BOMB };
  std::tuple<int, int> pos;
  BrickType type;
  int color; // 256 per channel RGB color
};

class GameState {
  bool _is_running = true;
  double _pad_pos;
  double _x_ball, _y_ball;
  double _vx_ball, _vy_ball;
  std::map<std::tuple<int, int>, Brick> _bricks;
  PhysicsEngine engine;
public:
  GameState();
  void exit();
  bool is_running() const;
  void use_power();
  void next_step();
  void display();
};

extern GameState game;

}
