#include "PNGImage.hpp"
#include "Button.hpp"


/**
 * @namespace view
 * A collection of view utilities
 */

namespace view {


struct ImageException : public std::exception {
  const std::string msg;
  ImageException(const std::string& msg) : std::exception(), msg(msg) { }
  const char* what() const noexcept override {
    return msg.c_str();
  }
};

};
