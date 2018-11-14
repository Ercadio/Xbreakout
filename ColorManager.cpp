#include "breakout.hpp"

namespace breakout {

ColorManager::ColorManager(Display* display, int screen_id) :
black(BlackPixel(display, screen_id)),
white(WhitePixel(display, screen_id)),
whale(),
rose(),
lime(),
lavender()
{ }

} // namespace
