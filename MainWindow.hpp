#pragma once
#include <X11/Xlib.h>
#include "breakout.hpp"
#include <string>

namespace breakout {

/**
  @class MainWindow
  The main window of the game
*/
class MainWindow {
  Display* _display;
  Window _wind;
  int screen_id;
  
public:
  static const std::string DEFAULT_NAME;

  MainWindow(Display* display = XOpenDisplay(nullptr),
               const std::string& name = MainWindow::DEFAULT_NAME);

  /**
    Sets the title of the window
    @param name the new name of the window
    @todo ensures it does not create memory leaks
  */  
  void set_title(const std::string& name);

};


}
