#pragma once
#include <initializer_list>
#include <stdexcept>

/**
 *  @class Matrix
 *  A Matrix utility class
 */

/**
 *  The primary template
 */
template <class T = double, int... shape>
class Matrix {

public:
  
  
  T* _data[(... * shape)];

  //template <class V, class U, int...dim>
  //friend Matrix<V, ...dim> operator*(U& scalar, Matrix<V, ...dim>& m);

/*
  template <class T1, int dim1, class T2, int dim2>
  friend operator*(Matrix<T1, dim1>& v1, Matrix<T2, dim2>& v2);

  template <
  friend operator+(T& scalar, Matrix& vec);
*/
};


/**
 *  A partial specialization
 */
template <class T, int first, int... rest>
class Matrix<T, first, rest...> {

public:

  using list_form = std::initializer_list<
                    typename Matrix<T, rest...>::list_form
               >;


  Matrix(list_form data) {
    if (data.size() != first) {
      throw std::length_error("Received " + std::to_string(data.size()) + 
                              " element for a dimension of " + std::to_string(first));
    }
  }

};

/**
 *  A partial specialization
 */
template <class T, int first>
class Matrix<T, first> {

public:

  using list_form = std::initializer_list<T>;

  Matrix(list_form data) {
    if (data.size() != first) {
      throw std::length_error("Received " + std::to_string(data.size()) + 
                              " element for a dimension of " + std::to_string(first));
    }
  }

};

typedef Matrix<double, 2> Vector;

