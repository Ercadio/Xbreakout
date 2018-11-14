#include "breakout.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include "view/view.hpp"

using namespace std::chrono_literals;

void skipUntil(Display* display, int eventType);


int main(int argc, char* argv[]) {

  // Default DISPLAY to localhost
  // This does not overwrite the env var
  setenv("DISPLAY", ":0", 0);

  std::cout << "[INFO] Using X Server at " << std::getenv("DISPLAY") << std::endl;

  /*
  XSetForeground(dpy, gc, whiteColor);
  XSetFillStyle(dpy, gc, FillSolid);
  
  std::cout << "[INFO] Skipping until MapNotify" << std::endl;
  skipUntil(dpy, MapNotify);

  std::cout << "[INFO] Drawing line" << std::endl;
  XDrawLine(dpy, window, gc, 0, 0, 100, 100); 
  
  XSync(dpy, screen_id);
  */
  Display* display = XOpenDisplay(nullptr);
  breakout::MainWindow* window = new breakout::MainWindow(display);
  breakout::EventManager* eventManager = new breakout::EventManager(display, [](const XEvent& event){
    switch(event.type) {
      case Expose:
        break;
      case DestroyNotify:
      case ClientMessage:
        std::cout << "[INFO] Quitting the application" << std::endl;
        breakout::game.exit();
        break;
      default:
        std::cerr << "[WARNING] Encountered unknown event" << std::endl;
        break;
    }
  });
  eventManager->registerDefaults(window);
  view::PNGImage img("test.png");


  XGCValues values;
  values.cap_style = CapButt;
  values.join_style = JoinBevel;
  GC gc = XCreateGC(display, window, GCCapStyle | GCJoinStyle, &values);
  if(gc < 0) {
    std::cout << "[FATAL] Unable to create Graphical context\n";
    std::exit(1);
  }

  window->map();
  eventManager->skipUntil(MapNotify);
  img.display(dpy, window, gc);
  while(breakout::game.is_running()) {
    std::cout << "[INFO] Game has started" << std::endl;
    
    eventManager->handleNext();
    std::this_thread::sleep_for(1000ms / 60);
  }

  delete window;
  delete eventManager;
  XCloseDisplay(display);

}


