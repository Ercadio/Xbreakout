#include "EventManager.hpp"

namespace breakout {

EventManager::EventManager(Display* display, std::function<void(const XEvent&)> handler) :
_display(display),
_handle(handler)
{ }

void EventManager::registerEvents(MainWindow* window, long mask) {
  XSelectInput(_display, window->_wind, mask);
}

void EventManager::registerDefaults(MainWindow* window) {
  Atom WM_DELETE_WINDOW = XInternAtom(_display, "WM_DELETE_WINDOW", false);
  XSetWMProtocols(_display, window->_wind, &WM_DELETE_WINDOW, 1);
  registerEvents(window, StructureNotifyMask | KeyPressMask | PointerMotionMask);
}

void EventManager::skipUntil(long mask) {
  std::cout << "[INFO] Skipping all upcoming events until " << mask << std::endl;
  XEvent e;
  do {
    XNextEvent(_display, &e);
    std::cout << "[INFO] Skipped event " << e.type << std::endl;
  } while(not (e.type | mask));
  std::cout << "[INFO] Received event " << e.type << " so we stop skipping" << std::endl;
}

void EventManager::handleNext() {
  std::cout << "[INFO] Listening to event" << std::endl;
  XEvent e;
  XNextEvent(_display, &e);
  std::cout << "[INFO] Handled event " << e.type << std::endl;
  _handle(e);
} 

} // namespace

