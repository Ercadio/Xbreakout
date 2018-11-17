#include "view.hpp"
#include <algorithm>
#include <iostream>
#include "../MainWindow.hpp"
#include "../EventManager.hpp"

namespace view {

Button::Button(std::string&& name, std::tuple<int, int> p1, std::tuple<int, int> p2) :
_imgdta((std::get<0>(p2) - std::get<0>(p1)) * (std::get<1>(p2) - std::get<1>(p1))),
_x1(std::get<0>(p1)),
_y1(std::get<1>(p1)),
_x2(std::get<0>(p2)),
_y2(std::get<1>(p2))
{
  std::fill(_imgdta.begin(), _imgdta.end(), 0xff);
  std::cout << "[INFO] Button was constructed" << std::endl;
}

void Button::display(Display* display, breakout::MainWindow* window, GC& gc) {
  XImage* ximg = XCreateImage(
    display, XDefaultVisual(display, 0),
    24, ZPixmap, 0,
    _imgdta.data(),
    _x2 - _x1,
    _y2 - _y1,
    32, 0
  );
  std::cout << "[INFO] Created button's image" << std::endl;
  XPutImage(display, window->drawable(), gc, ximg, 0, 0,
    _x1, _y1, 
    _x2 - _x1,
    _y2 - _y1
  );
  std::cout << "[INFO] Displayed button's image" << std::endl;
}

} // namespace
