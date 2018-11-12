#include "view.hpp"
#include <fstream>
#include <png.h>
#include <iostream>

namespace view {

PNGImage::PNGImage(const std::string& fp) :
imgdta(50*50*4)
{ 
  /*std::ifstream ifs(fp, std::ios::binary|std::ios::ate);
  std::ifstream::pos_type pos = ifs.tellg();
  std::vector<std::byte> result(pos);
  ifs.seekg(0, std::ios::beg);
  ifs.read(result.data(), pos);
*/
  /* if(not pnf_sig_cmp(???, 0, ???)) {
    throw ViewException("The file " + fp + " is not a png file");
  }

  png_structp png_ptr = png_create_read_struct(
    PNG_LIBPNG_VER_STRING, (png_voidp) user_error_ptr,
    user_error_fn, user_warning_fn
  );

  if(not png_ptr)
    throw ViewException("The file " + fp + " is not a png file");
  
  png_read_row(png_ptr); */


  // Testing
  for(int i = 0; i < 50; ++i) {
    for(int j = 0; j < 50; ++j) {
      if((i/10) % 2 == (j/10)%2) {
        imgdta[(i + 50 * j) * 4 + 0] = 0xff;
        imgdta[(i + 50 * j) * 4 + 1] = 0xff;
        imgdta[(i + 50 * j) * 4 + 2] = 0xff;
      } else {
        imgdta[(i + 50 * j) * 4 + 0] = 0xff;
        imgdta[(i + 50 * j) * 4 + 1] = 0x0;
        imgdta[(i + 50 * j) * 4 + 2] = 0xff;
      }
    }
  }

}


void PNGImage::display(Display* display, Window window, GC& gc) {
  std::cout << "[INFO] Displaying image" << std::endl;
  XImage* ximg= XCreateImage(
    display, XDefaultVisual(display, 0),
    24, ZPixmap, 0,
    imgdta.data(), 50, 50,
    32, 0
  );
  std::cout << "[INFO] Created image" << std::endl;
  XPutImage(display, window, gc, ximg, 0, 0,
    0, 0, 50, 50);
  std::cout << "[INFO] Displayed image" << std::endl;
  
}

}
