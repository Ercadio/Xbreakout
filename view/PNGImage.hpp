#pragma once
#include <cstddef>
#include <string>
#include <vector>
#include <tuple>
#include <X11/Xlib.h>

namespace view {

class PNGImage {

std::vector<char> _imgdta;
std::size_t _width;
std::size_t _height;

public:

  /**
   * Creates a PNGImage object given a file
   * @param fp the file path
   */
  PNGImage(const std::string& fp);

  /**
   * Displays the image
   * @param display the X11 connection
   * @param screen_id the target screen
   */
  void display(Display* display, Window window, GC& gc);

};

/**
 * Generates raw pixel data given a png file path
 * @paramfp the filepath
 * @relates PNGImage
 * @returns (row_data, height, width) where row_data is a list of pointers to the rows of the image 
 */
std::tuple<unsigned char**, int, int> getPNGPixels(const std::string& fn);

} // namespace

