#pragma once
#include <cstddef>
#include <string>
#include <vector>
#include <tuple>
#include <X11/Xlib.h>

namespace breakout { class MainWindow; }

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
   * @param window the target window
   * @param gc the graphical context
   * @param x the x coordinate
   * @param y the y coordinate
   */
  void display(Display* display, breakout::MainWindow* window, GC& gc, int x, int y);

};

/**
 * Generates raw pixel data given a png file path
 * @paramfp the filepath
 * @relates PNGImage
 * @returns (row_data, height, width) where row_data is a list of pointers to the rows of the image 
 */
std::tuple<unsigned char**, int, int> getPNGPixels(const std::string& fn);

} // namespace

