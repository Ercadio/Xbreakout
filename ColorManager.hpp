#pragma once
#include <X11/Xlib.h>
namespace breakout {

/**
  @struct ColorManager
  A set of colors
  @todo add more colors
*/
struct ColorManager {

  /**
    Creates a ColorSet for a screen
    @param display the X11 connection
    @param screen_id the affected screen's ID
  */
  ColorManager(Display* display, int screen_id);

  /** #000000 */
  const long unsigned int black;
  /** #FFFFFF */
  const long unsigned int white;
  /** #1C5D99 */
  const long unsigned int whale;
  /** #BF4342 */
  const long unsigned int rose;
  /** #7FB800 */
  const long unsigned int lime;
  /** #7871AA */
  const long unsigned int lavender;

};

} // namespace
