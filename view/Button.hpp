#pragma once
#include <tuple>
#include <string>
#include <X11/Xlib.h>

namespace breakout { class MainWindow; class EventManager; }

namespace view {

class Button {

std::vector<char> _imgdta;
int _x1, _y1, _x2, _y2;

public:
  /**
   * Creates a Button object
   * @param name the text to be displayed
   * @param p1 the left-top most coordinate
   * @param p2 the right-bottom most coordinate
   */
  Button(std::string&& name, std::tuple<int, int> p1, std::tuple<int, int> p2);
  
  /**
   * Displays the button
   * @param display the X11 connection
   * @param window the target window
   * @param gc the graphical context
   */
  void display(Display* display, breakout::MainWindow* window, GC& gc);

  /**
   * Registers the button with the event manager
   * @param manager the event manager
   */
  void registerClickable(breakout::EventManager& manager);
};

} // namespace
