#pragma once

#include <X11/Xlib.h>
#include <functional>
#include "MainWindow.hpp"

namespace breakout {

/**
  @class EventManger
  The manager of events
*/
class EventManager {
  Display* _display;
  std::function<void(const XEvent&)> _handle;
public:

  /**
    @param display the X11 connection
    @param handler the handler for events
  */
  EventManager(Display* display, std::function<void(const XEvent&)> handler);

  /**
    Subscribe to a type of event
    @param window the affected window
    @param mask the type(s) of event
  */
  void registerEvents(MainWindow* window, long mask);

  /**
    Register for all EventManager::DEFAULT_EVENTS
    @param window the affected window
  */
  void registerDefaults(MainWindow* window);

  /**
    Skips all event until an expected event is received
    @param mask the possible events to be expected
  */
  void skipUntil(long mask);

  /**
    Handles the next event received if available
    according to the defined handler
    @see EventManager::EventManager
  */
  void handleNext();
  
};



} // namespace
