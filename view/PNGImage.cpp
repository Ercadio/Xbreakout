#include "view.hpp"
#include <fstream>
#include <png.h>
#include <iostream>

namespace view {

PNGImage::PNGImage(const std::string& fp) {
  unsigned char** raw_rows;
  std::tie(raw_rows, _height, _width) = getPNGPixels(fp);
  _imgdta = std::vector<char>(_width * _height * 4);
  
  std::cout << "[INFO] Image is being copied" << std::endl; 

  for(unsigned int i = 0; i < _height; ++i) {
    _imgdta.insert(_imgdta.begin(), raw_rows[i], raw_rows[i] + _width * 4);
  }
 
  std::cout << "[INFO] Image was constructed" << std::endl; 

}


void PNGImage::display(Display* display, MainWindow* window, GC& gc) {
  std::cout << "[INFO] Displaying image" << std::endl;
  XImage* ximg= XCreateImage(
    display, XDefaultVisual(display, 0),
    24, ZPixmap, 0,
    _imgdta.data(), _width, _height,
    32, 0
  );
  std::cout << "[INFO] Created image" << std::endl;
  XPutImage(display, window->_wind, gc, ximg, 0, 0,
    0, 0, _width, _height);
  std::cout << "[INFO] Displayed image" << std::endl;
  
}

}
