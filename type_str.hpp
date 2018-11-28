#pragma once
#include <string>

template <class T>
struct type_str {
  static std::string value() { return "[unknown name]"; };
};

template <>
struct type_str<bool> {
  static std::string value() { return "bool"; }
};

template <>
struct type_str<int> {
  static std::string value() { return "int"; }
};

template <>
struct type_str<float> {
  static std::string value() { return "float"; }
};

template <>
struct type_str<double> {
  static std::string value() { return "double"; }
};
