#include <X11/Xlib.h>
#include <iostream>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;

void skipUntil(Display* display, int eventType);


int main(int argc, char* argv[]) {

  Display* dpy = XOpenDisplay(nullptr);
  if(dpy == nullptr) {
    std::cout << "[FATAL] Unable to open display\n";
    std::exit(1);
  }

  int screen_id = DefaultScreen(dpy);
  int blackColor = BlackPixel(dpy, screen_id);
  int whiteColor = WhitePixel(dpy, screen_id);
  int win_w = DisplayWidth(dpy, screen_id) / 2;
  int win_h = DisplayHeight(dpy, screen_id);

  Window window = XCreateSimpleWindow(dpy, DefaultRootWindow(dpy), 0, 0, win_w, win_h,
   0, blackColor, blackColor);

  //XSelectInput(dpy, window, StructureNotifyMask);
  XMapWindow(dpy, window);
  XGCValues values;
  values.cap_style = CapButt;
  values.join_style = JoinBevel;
  GC gc = XCreateGC(dpy, window, GCCapStyle | GCJoinStyle, &values);
  if(gc < 0) {
    std::cout << "[FATAL] Unable to create Graphical context\n";
    std::exit(1);
  }

  XSetForeground(dpy, gc, whiteColor);
  XSetFillStyle(dpy, gc, FillSolid);
  
  skipUntil(dpy, MapNotify);

  XDrawLine(dpy, window, gc, 20, 20, 100, 100); 

  XSync(dpy, screen_id);

  handleEvents(display);

}

void skipUntil(Display* display, int eventType) {
  XEvent e;
  do {
    XNextEvent(display, &e);
    std::cout << "[INFO] Received event " << e.type << std::endl;
  } while(e.type != eventType);
}

void handleEvents(Display* display) {
  XEvent e;
  do {
    switch(e.type) {
      case Expose:
        if(e.xexpose.count > 0)
          break;
        break;
      default:
        break;
    }
  } while(e.type != 0);
}
