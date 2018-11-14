#pragma once
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/Xrender.h>
#include "ColorManager.hpp"
#include <string>
#include <iostream>

namespace view { class PNGImage; }


namespace breakout {

/**
  @class MainWindow
  The main window of the game
*/
class MainWindow {
  Display* _display;
  int _screen_id;
  ColorManager _color;
  Window _wind;
  XSizeHints* _hint;
public:

  static const std::string DEFAULT_NAME;

  /**
    @param display the X11 connection
    @param name the name of the window
  */
  MainWindow(Display* display = XOpenDisplay(nullptr),
               const std::string& name = MainWindow::DEFAULT_NAME);

  /**
    Sets the title of the window
    @param name the new name of the window
    @todo implement
    @todo ensures it does not create memory leaks
  */  
  void set_title(const std::string& name);

  /**
    Maps the window to the display
  */
  void map();

  friend class EventManager;
  friend class view::PNGImage;

  /**
    Returns the window's drawable
  */ 
  long unsigned int drawable() const { return _wind; }

  /**
    Returns the window's id
  */
  long unsigned int id() const { return _screen_id; }

  int width() const { return DisplayWidth(_display, _screen_id)/2; }
  int height() const { return DisplayHeight(_display, _screen_id)/2; }
};


}
