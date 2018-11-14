#include "breakout.hpp"

namespace breakout {

const std::string MainWindow::DEFAULT_NAME = "Breakout";

MainWindow::MainWindow(Display* display, const std::string& name) :
_display(display),
_screen_id(DefaultScreen(_display)),
_color(ColorManager(_display, _screen_id)),
_wind(
  XCreateWindow(
    _display, 
    RootWindow(_display, _screen_id),
    DisplayWidth(_display, _screen_id) / 4, DisplayHeight(_display, _screen_id) / 4, 
    DisplayWidth(_display, _screen_id) / 2, DisplayHeight(_display, _screen_id) / 2, 
    0, 0, InputOutput, XDefaultVisual(_display, _screen_id),
    CWBackPixel, new XSetWindowAttributes{ 0, background_pixel: _color.black, 0 }
  )
),
_hint(new XSizeHints{ 
  flags: PPosition, 
  x: DisplayWidth(_display, _screen_id) / 4, 
  y: DisplayHeight(_display, _screen_id) / 4,
  0
})
{
  if (_display == nullptr) {
    std::cerr << "[FATAL] Unable to open display" << std::endl;
    throw DisplayException("Unable to open display");
  }
  XSetNormalHints(_display, _wind, _hint);
  set_title(name);
}


void MainWindow::set_title(const std::string& name) {

  XStoreName(_display, _wind, name.c_str());
/*  XTextProperty title;
  char** text = new char*[1];
  *text = name.c_str();
  XmbTextListToTextProperty(
    _display, text, 1, 
    XStringStyle, &title
  );
  XSetWMName(_display, _wind, &title);
*/}

void MainWindow::map() {
  std::cout << "[INFO] Mapped window " << _screen_id << std::endl;
  XMapWindow(_display, _wind);
  XSync(_display, _wind);
}

} // namespace
