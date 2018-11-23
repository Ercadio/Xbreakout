#pragma once
#include <initializer_list>
#include <stdexcept>
#include <ostream>
#include <vector>

/**
 *  @class Matrix
 *  A Matrix utility class
 *  @tparam T the numerical type
 *  @tparam ...shape the shape of the Matrix
 *  @todo Actually store data
 *  @todo Reimplement operator<<
 *  @todo Implement operator[] accessor
 *  @todo Implement + * / - operators for scalars
 *  @todo Implement + * / - operators between matrices
 *  @todo Implement .sum()
 *  @todo Implement .dot(const Matrix&) const
 *  @todo Implement > < >= <= MatrixSelectors
 */
template <class T = double, int... shape>
class Matrix;

/**
 *  @struct MatrixSelector
 *  A structure that holds information about a query to a Matrix
 *  @todo Design something better
 *  @todo Create tests and use cases about selectors
 */
template <int... shape>
struct MatrixSelector { };

template <int... shape>
MatrixSelector<shape...> operator"" _sel(const char* str);

template <class T, int... shape>
std::ostream& operator<<(std::ostream& os, const Matrix<T, shape...>& m);
template <class V, class U, int...dim>
Matrix<V, dim...> operator*(U scalar, Matrix<V, dim...> m);
template <class T1, int... dim1, class T2, int... dim2>
Matrix<T2, dim2...> operator*(Matrix<T1, dim1...> v1, Matrix<T2, dim2...> v2);
template <class V, class U, int...dim>
Matrix<V, dim...> operator/(Matrix<V, dim...> m, U scalar);
template <class T1, int... dim, class T2>
Matrix<T2, dim...> operator/(Matrix<T1, dim...> v1, Matrix<T2, dim...> v2);
template <class V, class U, int...dim>
Matrix<V, dim...> operator+(U scalar, Matrix<V, dim...> m);
template <class T1, int... dim, class T2>
Matrix<T2, dim...> operator+(Matrix<T1, dim...> v1, Matrix<T2, dim...> v2);
template <class V, class U, int...dim>
Matrix<V, dim...> operator-(Matrix<V, dim...> m, U scalar);
template <class T1, int... dim, class T2>
Matrix<T1, dim...> operator-(Matrix<T1, dim...> v1, Matrix<T2, dim...> v2);
Matrix<T, shape...> operator[](MatrixSelector<shape...>)

/**
 *  The primary template
 */
template <class T, int... shape>
class Matrix {

  T _data[(shape * ...)];

public: 
  
  friend std::ostream& operator<< <>(std::ostream& os, const Matrix<T, shape...>& m);
  
  template <class V, class U, int...dim>
  friend Matrix<V, dim...> operator*(U scalar, Matrix<V, dim...> m);
  template <class T1, int... dim1, class T2, int... dim2>
  friend Matrix<T2, dim2...> operator*(Matrix<T1, dim1...> v1, Matrix<T2, dim2...> v2);

  template <class V, class U, int...dim>
  friend Matrix<V, dim...> operator/(Matrix<V, dim...> m, U scalar);
  template <class T1, int... dim, class T2>
  friend Matrix<T2, dim...> operator/(Matrix<T1, dim...> v1, Matrix<T2, dim...> v2);

  template <class V, class U, int...dim>
  friend Matrix<V, dim...> operator+(U scalar, Matrix<V, dim...> m);
  template <class T1, int... dim, class T2>
  friend Matrix<T2, dim...> operator+(Matrix<T1, dim...> v1, Matrix<T2, dim...> v2);

  template <class V, class U, int...dim>
  friend Matrix<V, dim...> operator-(Matrix<V, dim...> m, U scalar);
  template <class T1, int... dim, class T2>
  friend Matrix<T1, dim...> operator-(Matrix<T1, dim...> v1, Matrix<T2, dim...> v2);

  template <class U>
  T dot(Matrix<U, shape...> m);
};


/**
 *  A partial specialization
 */
template <class T, int first, int... rest>
class Matrix<T, first, rest...> {

  T _data[first * (rest * ...)];

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
  
  friend std::ostream& operator<< <>(std::ostream& os, const Matrix<T, first, rest...>& m);

  template <class V, class U, int...dim>
  friend Matrix<V, dim...> operator*(U scalar, Matrix<V, dim...> m);
  template <class T1, int... dim1, class T2, int... dim2>
  friend Matrix<T2, dim2...> operator*(Matrix<T1, dim1...> v1, Matrix<T2, dim2...> v2);

  template <class V, class U, int...dim>
  friend Matrix<V, dim...> operator/(Matrix<V, dim...> m, U scalar);
  template <class T1, int... dim, class T2>
  friend Matrix<T2, dim...> operator/(Matrix<T1, dim...> v1, Matrix<T2, dim...> v2);

  template <class V, class U, int...dim>
  friend Matrix<V, dim...> operator+(U scalar, Matrix<V, dim...> m);
  template <class T1, int... dim, class T2>
  friend Matrix<T2, dim...> operator+(Matrix<T1, dim...> v1, Matrix<T2, dim...> v2);

  template <class V, class U, int...dim>
  friend Matrix<V, dim...> operator-(Matrix<V, dim...> m, U scalar);
  template <class T1, int... dim, class T2>
  friend Matrix<T1, dim...> operator-(Matrix<T1, dim...> v1, Matrix<T2, dim...> v2);

  template <class U>
  T dot(Matrix<U, first, rest...> m);
};

/**
 *  A partial specialization
 */
template <class T, int first>
class Matrix<T, first> {

  T _data[first];

public:

  using list_form = std::initializer_list<T>;

  Matrix(list_form data) {
    if (data.size() != first) {
      throw std::length_error("Received " + std::to_string(data.size()) + 
                              " element for a dimension of " + std::to_string(first));
    }
  }
  
  friend std::ostream& operator<< <>(std::ostream& os, const Matrix<T, first>& m);

  template <class V, class U, int...dim>
  friend Matrix<V, dim...> operator*(U scalar, Matrix<V, dim...> m);
  template <class T1, int... dim1, class T2, int... dim2>
  friend Matrix<T2, dim2...> operator*(Matrix<T1, dim1...> v1, Matrix<T2, dim2...> v2);

  template <class V, class U, int...dim>
  friend Matrix<V, dim...> operator/(Matrix<V, dim...> m, U scalar);
  template <class T1, int... dim, class T2>
  friend Matrix<T2, dim...> operator/(Matrix<T1, dim...> v1, Matrix<T2, dim...> v2);

  template <class V, class U, int...dim>
  friend Matrix<V, dim...> operator+(U scalar, Matrix<V, dim...> m);
  template <class T1, int... dim, class T2>
  friend Matrix<T2, dim...> operator+(Matrix<T1, dim...> v1, Matrix<T2, dim...> v2);

  template <class V, class U, int...dim>
  friend Matrix<V, dim...> operator-(Matrix<V, dim...> m, U scalar);
  template <class T1, int... dim, class T2>
  friend Matrix<T1, dim...> operator-(Matrix<T1, dim...> v1, Matrix<T2, dim...> v2);

  template <class U>
  T dot(Matrix<U, first> m);
};

typedef Matrix<double, 2> Vector;

template <class T, int... shape>
std::ostream& operator<<(std::ostream& os, const Matrix<T, shape...>& m) {
  os << "Matrix " << &m << " {\n";
  for(const T* it = m._data; it != m._data + (shape * ...); ++it) {
    os << *it << ", ";
  }
  os << "\b\b\b\b\n}" << std::endl;
  return os;
}
