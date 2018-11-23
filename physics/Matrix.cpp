#include "Matrix.hpp"



MatrixSelector operator"" _sel(const char* str) {
  MatrixSelector ms;
  char *eit;
  eit = const_cast<char*>(str) - 1;
  while(eit[0] != '\0') {
    int val = 0;
    eit = eit + 1;
    while(eit[0] - '0' < 10 and eit[0] >= '0') { 
      val = eit[0] - '0' + 10 * val;
      ++eit;
    }
    ms.specs.emplace_back(val);
  }
  return ms;
}

