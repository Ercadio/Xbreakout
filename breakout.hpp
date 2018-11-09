#pragma once
#include <exception>

namespace breakout {

struct DisplayException : public std::exception {
  const char* what() const noexcept override {
    return "A problem occured while trying to display.\n";
  }
};

}
