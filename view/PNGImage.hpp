#pragma once
#include <cstddef>
#include <string>
#include <vector>
#include <X11/Xlib.h>

namespace view {

class PNGImage {

std::vector<char> imgdta;

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

} // namespace
