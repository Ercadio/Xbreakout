#include "MainWindow.hpp"

namespace breakout {

const std::string MainWindow::DEFAULT_NAME = "breakout";

MainWindow::MainWindow(Display* display, const std::string& name) :
_display(display)
{
  if (_display == nullptr) {
    throw DisplayException();
  }
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

} // namespace
