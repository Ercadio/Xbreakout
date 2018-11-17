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

  Display* display = XOpenDisplay(nullptr);
  breakout::MainWindow* window = new breakout::MainWindow(display);
  breakout::EventManager* eventManager = new breakout::EventManager(display, [](const XEvent& event){
    switch(event.type) {
      case Expose:
        std::cout << "[INFO] Received Expose event" << std::endl;
        break;
      case KeyPress:
        std::cout << "[INFO] Pressed key " << event.xkey.state << " aka " << event.xkey.keycode << std::endl;
        if(event.xkey.keycode == 65)
          breakout::game.use_power();
        if(event.xkey.keycode == 9) {
          std::cout << "[INFO] Quitting the application" << std::endl;
          breakout::game.exit();
        }
        break;
      case MotionNotify:
        std::cout << "[INFO] Moved cursor" << std::endl;
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
  view::PNGImage img("assets/breakout.png");
  view::PNGImage esc("assets/esc.png");

  XGCValues values;
  values.cap_style = CapButt;
  values.join_style = JoinBevel;
  GC gc = XCreateGC(display, window->drawable(), GCCapStyle | GCJoinStyle, &values);
  if(gc < 0) {
    std::cout << "[FATAL] Unable to create Graphical context\n";
    std::exit(1);
  }

  window->map();
  XSync(display, window->id());
  eventManager->skipUntil(MapNotify);
  img.display(display, window, gc, window->width() / 2, window->height() / 3);
  esc.display(display, window, gc, window->width() / 2, window->height() * 0.6f);
  XSync(display, window->id());

  std::cout << "[INFO] Game has started" << std::endl;
  double fps = 0;
  while(breakout::game.is_running()) {
    auto now = std::system_clock::now();
    eventManager->handleNext();
    breakout::game.display();
    std::this_thread::sleep_for(1000ms / 60);
    auto delta = std::system_clock::now() - now;
    fps = fps + ALPHA * (delta - fps);
  }

  delete window;
  delete eventManager;
  XCloseDisplay(display);

}
