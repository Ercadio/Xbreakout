#include "../Test.test.hpp"
#include <complex>
#include "../../type_str.hpp"
using namespace std::complex_literals;
namespace test {

bool ctor() {
  bool result = false;
  Matrix<int, 1,2,3,4> m1 = {
    {
      {
        {{1},{2},{3},{4}}, {{5},{6},{7},{8}}, {{9},{10},{11},{12}}
      },
      {
        {{13},{14},{15},{16}}, {{17},{18},{19},{20}}, {{21},{22},{23},{24}}
      }
    }
  };
  
  Matrix <double, 0> m2 = {};
  Matrix <double, 1,1,1,1,0> m3;
  Matrix <std::complex<double>, 2, 2> hermitian = {
    {{1.}, {1.-1i}},
    {{1.+1i}, {1.}}
  };

  // Conversion ctor
  Matrix<double, 1> mdoub = {
    {1.3}
  };
  Matrix<int, 1> mint = mdoub;
  if(mint != Matrix<int, 1>({{1}})) {
    std::cerr << failmsg << "mint should have been floored to {{1}}" << std::endl;
    std::cerr << "mint: " << mint << std::endl;
    result = true;
  }
  return result;
}

bool arith() {
  bool result = false;
  Matrix<double, 2,2> m1 = {
    {{0.},{0.}},
    {{0.},{0.}}
  };
  auto m2 = (1. + (1 + ((((m1 + 1) + 1.) - 1) - 1.))) / 2 * 2 / 2. * 2.;
  if(typeid(m2) != typeid(Matrix<double, 2, 2>)) {
    std::cerr << failmsg << "m2 should have been of type " << type_str<Matrix<double, 2, 2> >::value()
              << " but was of type " << type_str<decltype(m2)>::value() << std::endl;
    result = true;
  }
  auto m3 = m2 * 1i; // Should be complex
  if(typeid(m3) != typeid(Matrix<std::complex<double>, 2, 2>)) {
    std::cerr << failmsg << "m3 should have been of type " << type_str<Matrix<std::complex<double>, 2, 2> >::value()
              << " but was of type " << type_str<decltype(m3)>::value() << std::endl;
    result = true;
  }
  if(m3 != m1 or not (m3 == m1)) {
    std::cerr << failmsg << "m3 should have been equal to m1" << std::endl;
    std::cerr << "m3: " << m3;
    std::cerr << "m1: " << m1;
    result = true;
  }

  Matrix<int, 2, 2> m4 = {{{1},{0}}, {{0},{1}}};
  Matrix<int, 2, 2> expected = {{{2},{1}},{{1},{2}}};
  if(m4 + 1 != expected or not(m4 + 1 == expected) or 1 + m4 != expected or not(1 + m4 == expected)) {
    std::cerr << failmsg << "m4 was not incremented properly by 1" << std::endl;
    std::cerr << "m4 + 1: " << (m4 + 1) << std::endl;
    std::cerr << "1 + m4: " << (1 + m4) << std::endl;
    std::cerr << "expected: " << expected << std::endl;
    result = true;
  }
  expected = {{{2},{0}},{{0},{2}}};
  if(m4 * 2 != expected or not(m4 * 2 != expected) or 2 * m4 != expected or not(2 * m4 == expected)) {
    std::cerr << failmsg << "m4 was not scaled properly by 2" << std::endl;
    std::cerr << "m4 * 2: " << (m4 * 2) << std::endl;
    std::cerr << "2 * m4: " << (2 * m4) << std::endl;
    std::cerr << "expected: " << expected << std::endl;
    result = true;
  }
  if(m4 / 0.5f != expected or not(m4 / 0.5f == expected)) {
    std::cerr << failmsg << "m4 was not divided properly by 1/2" << std::endl;
    std::cerr << "m4 / 0.5f: " << (m4 / 0.5f) << std::endl;
    std::cerr << "expected: " << expected << std::endl;
    result = true;
  }
  Matrix<int, 2,2> m5 = {{{2},{2}},{{2},{2}}};
  expected = {{{2},{0}},{{0},{2}}};
  if(m4 * m5 != expected or m5 * m4 != expected or not(m4 * m5 == expected) or not(m5 * m4 == expected)) {
    std::cerr << failmsg << "m4 was not properly multiplied by m5" << std::endl;
    std::cerr << "m4 * m5: " << (m4 * m5) << std::endl;
    std::cerr << "m5 * m4: " << (m5 * m4) << std::endl;
    std::cerr << "expected: " << expected << std::endl;
    result = true;
  }
  expected = {{{1},{1}},{{1},{1}}};
  if(m5 / m5 != expected or not(m5 / m5 == expected)) {
    std::cerr << failmsg << "m5 was not properly divided by m5" << std::endl;
    std::cerr << "m5 / m5: " << (m5 / m5) << std::endl;
    std::cerr << "expected: " << expected << std::endl;
    result = true;
  }
  // Division by 0 tests
  bool has_thrown = false;
  try { m4 / m4; } catch(std::logic_error& e) {
    has_thrown = true;
  }
  if(not has_thrown) {
    std::cerr << failmsg << "m4 did not throw std::logic_error when dividied by itself" << std::endl;
    result = true;
  }
  has_thrown = false;
  try { m4 / 0; } catch(std::logic_error& e) {
    has_thrown = true;
  }
  if(not has_thrown) {
    std::cerr << failmsg << "m4 did not throw std::logic_error when dividied by 0" << std::endl;
    result = true;
  }
  expected = {{{2},{0}},{{0},{2}}};
  if(m4 + m4 != expected or not(m4 + m4 == expected)) {
    std::cerr << failmsg << "m4 + m4 was incorrect" << std::endl;
    std::cerr << "m4 + m4: " << (m4 + m4) << std::endl;
    std::cerr << "expected: " << expected << std::endl;
    result = true;
  }
  expected = m1;
  if(m4 - m4 != expected or not(m4 - m4 == expected)) {
    std::cerr << failmsg << "m4 - m4 was not zero matrix" << std::endl;
    std::cerr << "m4 - m4: " << (m4 - m4) << std::endl;
    std::cerr << "expected: " << expected << std::endl;
    result = true;
  }
  if(m4 - 2 != expected or not(m4 - 2 == expected)) {
    std::cerr << failmsg << "m4 - 2 was not zero matrix" << std::endl;
    std::cerr << "m4 - 2: " << (m4 - 2) << std::endl;
    std::cerr << "expected: " << expected << std::endl;
    result = true;
  }
  return result;
}


Suite MatrixSuite ("Matrix", { &ctor, &arith } );


}
