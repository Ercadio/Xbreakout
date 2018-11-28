#pragma once
#include <string>
#include <stdexcept>
#include <ostream>
#include <vector>
#include "../type_str.hpp"


template <class T, int... shape>
struct type_str<Matrix<T, shape...> > {
  static std::string value() {
    return std::string("Matrix<") + type_str<T>::value() + ", "
            + ((std::to_string(shape) + ", ") + ...) + ">";
  }
};

template <class T, int... shape>
std::ostream& operator<<(std::ostream& os, const Matrix<T, shape...>& m) {
  os << "Matrix " << &m << " {\n";
  for(const T* it = m._data; it != m._data + (shape * ...); ++it) {
    os << *it << ", ";
  }
  os << "\n}" << std::endl;
  return os;
}

template <class V, class U, int...dim>
Matrix<typename std::invoke_result_t<std::multiplies<>, U, V>, dim...>
operator*(U scalar, Matrix<V, dim...> m) {
  return m.template generate([&scalar](const V& v) -> V { return scalar * v; });
}

template <class V, class U, int...dim>
Matrix<typename std::invoke_result_t<std::multiplies<>, V, U>, dim...>
operator*(Matrix<V, dim...> m, U scalar) {
  return m.template generate([&scalar](const V& v) -> V { return v * scalar; });
}

template <class T1, int... dim1, class T2, int... dim2>
Matrix<typename std::invoke_result_t<std::multiplies<>, T1, T2>, dim2...>
operator*(Matrix<T1, dim1...> v1, Matrix<T2, dim2...> v2) {
  return {};
}

template <class V, class U, int...dim>
Matrix<typename std::invoke_result_t<std::divides<>, V, U>, dim...>
operator/(Matrix<V, dim...> m, U scalar) {
  return m.template generate([&scalar](const V& v) -> V { return v / scalar; });
}

template <class T1, int... dim, class T2>
Matrix<typename std::invoke_result_t<std::divides<>, T1, T2>, dim...>
operator/(Matrix<T1, dim...> v1, Matrix<T2, dim...> v2) {
  return {};
}

template <class V, class U, int...dim>
Matrix<typename std::invoke_result_t<std::plus<>, U, V>, dim...>
operator+(U scalar, Matrix<V, dim...> m) {
  return m.template generate([&scalar](const V& v) -> V { return scalar + v; });
}

template <class V, class U, int...dim>
Matrix<typename std::invoke_result_t<std::plus<>, V, U>, dim...>
operator+(Matrix<V, dim...> m, U scalar) {
  return m.template generate([&scalar](const V& v) -> V { return v + scalar; });
}

template <class T1, int... dim, class T2>
Matrix<typename std::invoke_result_t<std::plus<>, T1, T2>, dim...>
operator+(Matrix<T1, dim...> v1, Matrix<T2, dim...> v2) {
  return {};
}

template <class V, class U, int...dim>
Matrix<typename std::invoke_result_t<std::minus<>, V, U>, dim...>
operator-(Matrix<V, dim...> m, U scalar) {
  return m.template generate([&scalar](const V& v) -> V { return v - scalar; });
}

template <class T1, int... dim, class T2>
Matrix<typename std::invoke_result_t<std::minus<>, T1, T2>, dim...>
operator-(Matrix<T1, dim...> v1, Matrix<T2, dim...> v2) {
  return {};
}

template <class T, int... shape>
bool operator==  (const Matrix<T, shape...>& m1, const Matrix<T, shape...> m2) {
  return {}; //m1.generate(std::equal_to).allTrue();
}

template <class T, int... shape>
bool operator!= (const Matrix<T, shape...>& m1, const Matrix<T, shape...> m2) {
  return {}; //m1.generate(std::not_equal_to).allTrue();
}

template <class T, int... shape>
bool operator<= (const Matrix<T, shape...>& m1, const Matrix<T, shape...> m2) {
  return {}; //m1.generate(std::less_equal).allTrue();
}

template <class T, int... shape>
bool operator>= (const Matrix<T, shape...>& m1, const Matrix<T, shape...> m2) {
  return {}; //this->generate(std::greater_equal).allTrue();
}

template <class T, int... shape>
bool operator< (const Matrix<T, shape...>& m1, const Matrix<T, shape...> m2) {
  return {}; //this->generate(std::less).allTrue();
}

template <class T, int... shape>
bool operator> (const Matrix<T, shape...>& m1, const Matrix<T, shape...> m2) {
  return {}; //this->generate(std::greater).allTrue();
}

template <class T, int first, int... shape>
template <class U>
typename std::invoke_result_t<std::plus<>, 
  typename std::invoke_result_t<std::multiplies<>, T, U>,
  typename std::invoke_result_t<std::multiplies<>, T, U>
>
Matrix<T, first, shape...>::dot(const Matrix<U, first, shape...>& m) {
  return {};
}

template <class T, int first>
template <class U>
typename std::invoke_result_t<std::plus<>,
  typename std::invoke_result_t<std::multiplies<>, T, U>,
  typename std::invoke_result_t<std::multiplies<>, T, U>
>
Matrix<T, first>::dot(const Matrix<U, first>& m) {
  return {};
}

template <class T, int first, int... shape>
template <int... dim>
Matrix<T, dim...> Matrix<T, first, shape...>::operator[](const std::string& selector) {
  return {};
}

template <class T, int first>
template <int... dim>
Matrix<T, dim...> Matrix<T, first>::operator[](const std::string& selector) {
  return {};
}

template <class T, int first, int...rest>
Matrix<T, first, rest...>::Matrix() { }

template <class T, int first>
Matrix<T, first>::Matrix() { }

template <class T, int first, int... rest>
template <class U>
Matrix<T, first, rest...>::Matrix(const Matrix<U, first, rest...>& m) { }

template <class T, int first>
template <class U>
Matrix<T, first>::Matrix(const Matrix<U, first>& m) { }

template <class T, int first, int... rest>
template <class Functor>
Matrix<typename std::invoke_result_t<Functor, T>, first, rest...>
Matrix<T, first, rest...>::generate(Functor generator) {
  Matrix<typename std::invoke_result_t<Functor, T>, first, rest...> m;
  for(auto it = _data; it != _data + first * (rest * ...); ++it) {
    m._data[it - _data] = generator(it[0]);
  }
  return m;
}

template <class T, int first>
template <class Functor>
Matrix<typename std::invoke_result_t<Functor, T>, first>
Matrix<T, first>::generate(Functor generator) {
  Matrix<typename std::invoke_result_t<Functor, T>, first> m;
  for(auto it = _data; it != _data + first; ++it) {
    m._data[it - _data] = generator(it[0]);
  }
  return m;
}


