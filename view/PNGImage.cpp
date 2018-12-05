#include "view.hpp"
#include <fstream>
#include <png.h>
#include <iostream>
#include "../MainWindow.hpp"
#include "../logging.hpp"

namespace view {

PNGImage::PNGImage(const std::string& fp) {
  unsigned char** raw_rows;
  std::tie(raw_rows, _height, _width) = getPNGPixels(fp);
  _imgdta = std::vector<char>(_width * _height * 4);
  
  infomsg << "Image is being copied" << std::endl; 

  for(int i = _height - 1; i >= 0; --i) {
    _imgdta.insert(_imgdta.begin(), raw_rows[i], raw_rows[i] + _width * 4);
  }
 
  infomsg << "Image was constructed" << std::endl; 

}


void PNGImage::display(Display* display, breakout::MainWindow* window, GC& gc, int x, int y) {
  XImage* ximg= XCreateImage(
    display, XDefaultVisual(display, 0),
    24, ZPixmap, 0,
    _imgdta.data(), _width, _height,
    32, 0
  );
  infomsg << "Created image" << std::endl;
  XPutImage(display, window->drawable(), gc, ximg, 0, 0,
    x - _width/2, y - _height/2,  _width, _height);
  infomsg << "Displayed image to " << window->drawable() << std::endl;
  
}

}
