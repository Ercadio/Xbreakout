#include "breakout.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include "view/view.hpp"
#include "logging.hpp"

#define ALPHA 0.2f

using namespace std::chrono_literals;

void skipUntil(Display* display, int eventType);


int main(int argc, char* argv[]) {

  // Default DISPLAY to localhost
  // This does not overwrite the env var
  setenv("DISPLAY", ":0", 0);

  infomsg << "Using X Server at " << std::getenv("DISPLAY") << std::endl;

  Display* display = XOpenDisplay(nullptr);
  if(display == nullptr) {
    errormsg << "Failed to create display" << std::endl;
  }
  breakout::MainWindow* window = new breakout::MainWindow(display);
  breakout::EventManager* eventManager = new breakout::EventManager(display, [](const XEvent& event){
    switch(event.type) {
      case Expose:
        infomsg << "Received Expose event" << std::endl;
        break;
      case KeyPress:
        infomsg << "Pressed key " << event.xkey.state 
                  << " aka " << event.xkey.keycode << std::endl;
        if(event.xkey.keycode == 65)
          breakout::game.use_power();
        if(event.xkey.keycode == 9) {
          infomsg << "Quitting the application" << std::endl;
          breakout::game.exit();
        }
        break;
      case MotionNotify:
        debugmsg << "Moved cursor" << std::endl;
        break;
      case DestroyNotify:
      case ClientMessage:
        infomsg << "Quitting the application" << std::endl;
        breakout::game.exit();
        break;
      default:
        warningmsg << "Encountered unknown event" << std::endl;
        break;
    }
  });
  eventManager->registerDefaults(window);
  view::PNGImage img("assets/breakout.png");
  view::PNGImage esc("assets/esc.png");

  XGCValues values;
  values.cap_style = CapButt;
  values.join_style = JoinBevel;
  GC gc = XCreateGC(display, window->drawable(), GCCapStyle | GCJoinStyle, &values);

  window->map();
  XSync(display, window->id());
  eventManager->skipUntil(MapNotify);
  img.display(display, window, gc, window->width() / 2, window->height() / 3);
  esc.display(display, window, gc, window->width() / 2, window->height() * 0.6f);
  XSync(display, window->id());

  infomsg << "Game has started" << std::endl;
  double fps = 0;
  while(breakout::game.is_running()) {
    auto now = std::chrono::system_clock::now();
    eventManager->handleNext();
    breakout::game.display();
    std::this_thread::sleep_for(1000ms / 60);
    auto delta = std::chrono::system_clock::now() - now;
    fps = fps + ALPHA * (delta.count() - fps);
  }

  delete window;
  delete eventManager;
  XCloseDisplay(display);

}
