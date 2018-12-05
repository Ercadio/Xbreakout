#pragma once
#include <initializer_list>
#include <stdexcept>
#include <ostream>
#include <vector>
#include <functional>
#include <type_traits>

/**
 *  @class Matrix
 *  A Matrix utility class
 *  @tparam T the numerical type
 *  @tparam ...shape the shape of the Matrix
 *  @todo Actually store data
 *  @todo Implement .sum()
 *  @todo Implement .transpose()
 */
template <class T = double, int... shape>
class Matrix;

/**
 *  @struct is_Matrix
 *  @tparam T the type
 */
template<class T>
struct is_Matrix {
  static constexpr bool value = false;
};

template <class T, int... shape>
struct is_Matrix<Matrix<T, shape...> > {
  static constexpr bool value = true;
};

template <class T>
constexpr bool is_Matrix_v = is_Matrix<T>::value;

/**
 *  Prints the Matrix
 *  @tparam T the type of the Matrix
 *  @tparam ...shape the shape of the Matrix
 *  @param os the output stream
 *  @param m the Matrix
 *  @todo Reimplement better
 */
template<class T, int... shape>
std::ostream& operator<<(std::ostream& os, const Matrix<T, shape...>& m);

/**
 *  Returns true if two Matrix are equal
 *  @tparam T the type of the two Matrix
 *  @tparam ...shape the shape of the two Matrix
 *  @param m1 the first Matrix
 *  @param m2 the second Matrix
 *  @todo implement
 */
template<class T, int... shape>
bool operator==(const Matrix<T, shape...>& m1, const Matrix<T, shape...> m2);

/**
 *  Returns true if two Matrix are not equal
 *  @tparam T the type of the two Matrix
 *  @tparam ...shape the shape of the two Matrix
 *  @param m1 the first Matrix
 *  @param m2 the second Matrix
 *  @todo implement
 */
template<class T, int... shape>
bool operator!=(const Matrix<T, shape...>& m1, const Matrix<T, shape...> m2);

/**
 *  Returns a Matrix of booleans: true if the Matrix is smaller or equal than the other Matrix
 *  @tparam T the type of the two Matrix
 *  @tparam ...shape the shape of the two Matrix
 *  @param m1 the first Matrix
 *  @param m2 the second Matrix
 *  @todo change return type
 *  @todo implement
 */
template<class T, int... shape>
bool operator<=(const Matrix<T, shape...>& m1, const Matrix<T, shape...> m2);

/**
 *  Returns a Matrix of booleans: true if the Matrix is greater or equal than the other Matrix
 *  @tparam T the type of the two Matrix
 *  @tparam ...shape the shape of the two Matrix
 *  @param m1 the first Matrix
 *  @param m2 the second Matrix
 *  @todo change return type
 *  @todo implement
 */
template<class T, int... shape>
bool operator>=(const Matrix<T, shape...>& m1, const Matrix<T, shape...> m2);

/**
 *  Returns a Matrix of booleans: true if the Matrix is smaller than the other Matrix
 *  @tparam T the type of the two Matrix
 *  @tparam ...shape the shape of the two Matrix
 *  @param m1 the first Matrix
 *  @param m2 the second Matrix
 *  @todo change return type
 *  @todo implement
 */
template<class T, int... shape>
bool operator<(const Matrix<T, shape...>& m1, const Matrix<T, shape...> m2);

/**
 *  Returns a Matrix of booleans: true if the Matrix is greater than the other Matrix
 *  @tparam T the type of the two Matrix
 *  @tparam ...shape the shape of the two Matrix
 *  @param m1 the first Matrix
 *  @param m2 the second Matrix
 *  @todo change return type
 *  @todo implement
 */
template<class T, int... shape>
bool operator>(const Matrix<T, shape...>& m1, const Matrix<T, shape...> m2);

/**
 *  Returns a Matrix where each index is scaled
 *  @tparam U the type of the scalar
 *  @tparam V the type of the Matrix
 *  @tparam ...dim the shape of the Matrix
 *  @param scalar the scalar
 *  @param m the Matrix
 *  @todo implement
 */
template <class V, class U, int...dim>
std::enable_if_t<
  not is_Matrix_v<U>,
  Matrix<typename std::invoke_result_t<std::multiplies<>, U, V>, dim...>
>
operator*(U scalar, Matrix<V, dim...> m);

/**
 *  Returns a Matrix where each index is scaled
 *  @tparam U the type of the scalar
 *  @tparam V the type of the Matrix
 *  @tparam ...dim the shape of the Matrix
 *  @param scalar the scalar
 *  @param m the Matrix
 *  @todo implement
 */
template <class V, class U, int...dim>
std::enable_if_t<
  not is_Matrix_v<U>,
  Matrix<typename std::invoke_result_t<std::multiplies<>, V, U>, dim...>
>
operator*(Matrix<V, dim...> m, U scalar);

/**
 *  Returns a Matrix equal to the Matrix product of the two Matrix
 *  @tparam T1 the type of the first Matrix
 *  @tparam T2 the type of the second Matrix
 *  @tparam ...dim1 the shape of the first Matrix
 *  @tparam ...dim2 the shape of the second Matrix
 *  @param m1 the first Matrix
 *  @param m2 the second Matrix
 *  @pre the second dimensions must be the same or both do not exist (Matrix::outer logic see Matrix 's todo)
 *  @todo implement
 *  @todo move this logic to a method Matrix::outer instead and change this to the index-wise product of 
 *        two similarly-shaped Matrix (change templates)
 *  @todo change all the tests and code that use Matrix::operator* to Matrix::outer
 *  @todo specialize for three cases (Matrix::outer logic see Matrix 's todo):
 *    - The two Matrix have no dimensions (and are dynamically sized)
 *    - The two Matrix have a single dimension
 *    - The two Matrix have at least two dimensions
 */
template <class T1, int... dim1, class T2, int... dim2>
Matrix<typename std::invoke_result_t<std::multiplies<>, T1, T2>, dim2...>
operator*(Matrix<T1, dim1...> v1, Matrix<T2, dim2...> v2);

/**
 *  Returns a Matrix where each index is divided
 *  @tparam U the type of the scalar
 *  @tparam V the type of the Matrix
 *  @tparam ...dim the shape of the Matrix
 *  @param scalar the scalar
 *  @param m the Matrix
 *  @todo implement
*/
template <class V, class U, int...dim>
std::enable_if_t<
  not is_Matrix_v<U>,
  Matrix<typename std::invoke_result_t<std::divides<>, V, U>, dim...>
>
operator/(Matrix<V, dim...> m, U scalar);

/**
 *  Returns the index-wise division of two Matrix
 *  @tparam T1 the type of the first Matrix
 *  @tparam T2 the type of the second Matrix
 *  @tparam ...dim the shape of the two Matrix
 *  @param m1 the first Matrix
 *  @param m2 the second Matrix
 *  @todo implement
 */
template <class T1, int... dim, class T2>
Matrix<typename std::invoke_result_t<std::divides<>, T1, T2>, dim...>
operator/(Matrix<T1, dim...> m1, Matrix<T2, dim...> m2);

/**
 *  Returns an offseted Matrix
 *  @tparam V the type of the Matrix
 *  @tparam U the type of the offset
 *  @param offset the offset
 *  @param m the Matrix
 *  @todo implement
 */
template <class V, class U, int...dim>
std::enable_if_t<
  not is_Matrix_v<U>,
  Matrix<typename std::invoke_result_t<std::plus<>, U, V>, dim...>
>
operator+(U scalar, Matrix<V, dim...> m);

/**
 *  Returns an offseted Matrix
 *  @tparam V the type of the Matrix
 *  @tparam U the type of the offset
 *  @param offset the offset
 *  @param m the Matrix
 *  @todo implement
 */
template <class V, class U, int...dim>
std::enable_if_t<
  not is_Matrix_v<U>,
  Matrix<typename std::invoke_result_t<std::plus<>, V, U>, dim...>
>
operator+(Matrix<V, dim...> m, U scalar);

/**
 *  Returns the index-wise addition of two Matrix
 *  @tparam T1 the type of the first Matrix
 *  @tparam T2 the type of the second Matrix
 *  @tparam ...dim the shape of the two Matrix
 *  @param m1 the first Matrix
 *  @param m2 the second Matrix
 *  @todo implement
 */
template <class T1, int... dim, class T2>
Matrix<typename std::invoke_result_t<std::plus<>, T1, T2>, dim...>
operator+(Matrix<T1, dim...> m1, Matrix<T2, dim...> m2);

/**
 *  Returns an offseted Matrix
 *  @tparam V the type of the Matrix
 *  @tparam U the type of the offset
 *  @param offset the offset
 *  @param m the Matrix
 *  @todo implement
 */
template <class V, class U, int...dim>
std::enable_if_t<
  not is_Matrix_v<U>,
  Matrix<typename std::invoke_result_t<std::minus<>, V, U>, dim...>
>
operator-(Matrix<V, dim...> m, U scalar);

/**
 *  Returns the index-wise subtraction of two Matrix
 *  @tparam T1 the type of the first Matrix
 *  @tparam T2 the type of the second Matrix
 *  @tparam ...dim the shape of the two Matrix
 *  @param m1 the first Matrix
 *  @param m2 the second Matrix
 *  @todo implement
 */
template <class T1, int... dim, class T2>
Matrix<typename std::invoke_result_t<std::minus<>, T1, T2>, dim...>
operator-(Matrix<T1, dim...> v1, Matrix<T2, dim...> v2);

/**
 *  Returns the logical AND of two Matrix
 *  @tparam ...dim the shape of the two Matrix
 *  @param m1 the first Matrix
 *  @param m2 the second Matrix
 */
template <int... dim>
Matrix<bool, dim...> operator and(const Matrix<bool, dim...>& m1, const Matrix<bool, dim...>& m2);

/**
 *  Returns the logical OR of two Matrix
 *  @tparam ...dim the shape of the two Matrix
 *  @param m1 the first Matrix
 *  @param m2 the second Matrix
 */
template <int... dim>
Matrix<bool, dim...> operator or(const Matrix<bool, dim...>& m1, const Matrix<bool, dim...>& m2);

/**
 *  Returns the logical NOT of a Matrix
 *  @tparam ...dim the shape of the two Matrix
 *  @param m the Matrix
 */
template <int... dim>
Matrix<bool, dim...> operator not(const Matrix<bool, dim...>& m);

/**
 *  Returns the logical XOR of two Matrix
 *  @tparam ...dim the shape of the two Matrix
 *  @param m1 the first Matrix
 *  @param m2 the second Matrix
 */
template<int... dim>
Matrix<bool, dim...> operator xor(const Matrix<bool, dim...>& m1, const Matrix<bool, dim...>& m2);

/**
 *  A dynamically-shaped Matrix
 *  @todo change all these commented-out declarations correctly for the specialization
 */
template <class T>
class Matrix<T> {

public: 

/* (Vincent) See todo
 * above  
  Matrix();
  template <class U>
  Matrix(const Matrix<U, shape...>& m);

  friend std::ostream& operator<< <>(std::ostream& os, const Matrix<T, shape...>& m);
  
  template <class V, class U, int...dim>
  friend Matrix<V, dim...> operator*(U scalar, Matrix<V, dim...> m);
  template <class V, class U, int...dim>
  friend Matrix<V, dim...> operator*(Matrix<V, dim...> m, U scalar);
  template <class T1, int... dim1, class T2, int... dim2>
  friend Matrix<T2, dim2...> operator*(Matrix<T1, dim1...> v1, Matrix<T2, dim2...> v2);

  template <class V, class U, int...dim>
  friend Matrix<V, dim...> operator/(Matrix<V, dim...> m, U scalar);
  template <class T1, int... dim, class T2>
  friend Matrix<T2, dim...> operator/(Matrix<T1, dim...> v1, Matrix<T2, dim...> v2);

  template <class V, class U, int...dim>
  friend Matrix<V, dim...> operator+(U scalar, Matrix<V, dim...> m);
  template <class V, class U, int...dim>
  friend Matrix<V, dim...> operator+(Matrix<V, dim...> m, U scalar);
  template <class T1, int... dim, class T2>
  friend Matrix<T2, dim...> operator+(Matrix<T1, dim...> v1, Matrix<T2, dim...> v2);

  template <class V, class U, int...dim>
  friend Matrix<V, dim...> operator-(Matrix<V, dim...> m, U scalar);
  template <class T1, int... dim, class T2>
  friend Matrix<T1, dim...> operator-(Matrix<T1, dim...> v1, Matrix<T2, dim...> v2);

  friend bool operator== <>(const Matrix<T, shape...>& m1, const Matrix<T, shape...> m2);
  friend bool operator!= <>(const Matrix<T, shape...>& m1, const Matrix<T, shape...> m2);
  friend bool operator<= <>(const Matrix<T, shape...>& m1, const Matrix<T, shape...> m2);
  friend bool operator>= <>(const Matrix<T, shape...>& m1, const Matrix<T, shape...> m2);
  friend bool operator< <>(const Matrix<T, shape...>& m1, const Matrix<T, shape...> m2);
  friend bool operator> <>(const Matrix<T, shape...>& m1, const Matrix<T, shape...> m2);

  template <class U>
  T dot(const Matrix<U, shape...>& m);

  template <int... dim>
  Matrix<T, dim...> operator[](const std::string& selector);

  */
};

template <class T, int first, int... rest>
class Matrix<T, first, rest...> {

  T _data[first * (rest * ...)];

public:

  using list_form = std::initializer_list<
                      typename Matrix<T, rest...>::list_form
                    >;

  Matrix();
  Matrix(list_form data) {
    if (data.size() != first) {
      throw std::length_error("Received " + std::to_string(data.size()) + 
                              " element for a dimension of " + std::to_string(first));
    }
  }
  template <class U>
  Matrix(const Matrix<U, first, rest...>& m);
  
  friend std::ostream& operator<< <>(std::ostream& os, const Matrix<T, first, rest...>& m);

  template <class V, class U, int...dim>
  friend std::enable_if_t<
    not is_Matrix_v<U>,
    Matrix<typename std::invoke_result_t<std::multiplies<>, U, T>, first, rest...> 
  >
  operator*(U scalar, Matrix<T, first, rest...> m);

  template <class V, class U, int...dim>
  friend std::enable_if_t<
    not is_Matrix_v<U>,
    Matrix<typename std::invoke_result_t<std::multiplies<>, V, U>, dim...> 
  >
  operator*(Matrix<V, dim...> m, U scalar);

  template <class T1, int... dim1, class T2, int... dim2>
  friend Matrix<typename std::invoke_result_t<std::multiplies<>, T1, T2>, dim2...>
  operator*(Matrix<T1, dim1...> v1, Matrix<T2, dim2...> v2);

  template <class V, class U, int...dim>
  friend std::enable_if_t<
    not is_Matrix_v<U>,
    Matrix<typename std::invoke_result_t<std::divides<>, V, U>, dim...> 
  >
  operator/(Matrix<V, dim...> m, U scalar);

  template <class T1, int... dim, class T2>
  friend Matrix<typename std::invoke_result_t<std::divides<>, T1, T2>, dim...>
  operator/(Matrix<T1, dim...> v1, Matrix<T2, dim...> v2);

  template <class V, class U, int...dim>
  friend std::enable_if_t<
    not is_Matrix_v<U>,
    Matrix<typename std::invoke_result_t<std::plus<>, U, V>, dim...>
  >
  operator+(U scalar, Matrix<V, dim...> m);

  template <class V, class U, int...dim>
  friend std::enable_if_t<
    not is_Matrix_v<U>,
    Matrix<typename std::invoke_result_t<std::plus<>, V, U>, dim...>
  >
  operator+(Matrix<V, dim...> m, U scalar);

  template <class T1, int... dim, class T2>
  friend Matrix<typename std::invoke_result_t<std::plus<>, T1, T2>, dim...>
  operator+(Matrix<T1, dim...> v1, Matrix<T2, dim...> v2);

  template <class V, class U, int...dim>
  friend std::enable_if_t<
    not is_Matrix_v<U>,
    Matrix<typename std::invoke_result_t<std::minus<>, V, U>, dim...>
  >
  operator-(Matrix<V, dim...> m, U scalar);

  template <class T1, int... dim, class T2>
  friend Matrix<typename std::invoke_result_t<std::minus<>, T1, T2>, dim...>
  operator-(Matrix<T1, dim...> v1, Matrix<T2, dim...> v2);

  template <class U>
  typename std::invoke_result_t<std::plus<>, 
    typename std::invoke_result_t<std::multiplies<>, T, U>,
    typename std::invoke_result_t<std::multiplies<>, T, U>
  > 
  dot(const Matrix<U, first, rest...>& m);

  friend bool operator== <> (const Matrix<T, first, rest...>& m1, const Matrix<T, first, rest...> m2);
  friend bool operator!= <>(const Matrix<T, first, rest...>& m1, const Matrix<T, first, rest...> m2);
  friend bool operator<= <>(const Matrix<T, first, rest...>& m1, const Matrix<T, first, rest...> m2);
  friend bool operator>= <>(const Matrix<T, first, rest...>& m1, const Matrix<T, first, rest...> m2);
  friend bool operator< <>(const Matrix<T, first, rest...>& m1, const Matrix<T, first, rest...> m2);
  friend bool operator> <>(const Matrix<T, first, rest...>& m1, const Matrix<T, first, rest...> m2);

  template <int... dim>
  Matrix<T, dim...> operator[](const std::string& selector);

  template <class Functor>
  Matrix<typename std::invoke_result_t<Functor, T>, first, rest...> generate(Functor generator);

  template <class U, int... dim>
  friend class Matrix;

};

template <class T, int first>
class Matrix<T, first> {

  T _data[first];

public:

  using list_form = std::initializer_list<T>;

  Matrix();
  Matrix(list_form data) {
    if (data.size() != first) {
      throw std::length_error("Received " + std::to_string(data.size()) + 
                              " element for a dimension of " + std::to_string(first));
    }
  }
  template <class U>
  Matrix(const Matrix<U, first>& m);
  
  friend std::ostream& operator<< <>(std::ostream& os, const Matrix<T, first>& m);

  template <class V, class U, int...dim>
  friend std::enable_if_t<
    not is_Matrix_v<U>,
    Matrix<typename std::invoke_result_t<std::multiplies<>, U, V>, dim...>
  >
  operator*(U scalar, Matrix<V, dim...> m);

  template <class V, class U, int...dim>
  friend std::enable_if_t<
    not is_Matrix_v<U>,
    Matrix<typename std::invoke_result_t<std::multiplies<>, V, U>, dim...>
  >
  operator*(Matrix<V, dim...> m, U scalar);

  template <class T1, int... dim1, class T2, int... dim2>
  friend Matrix<typename std::invoke_result_t<std::multiplies<>, T1, T2>, dim2...>
  operator*(Matrix<T1, dim1...> v1, Matrix<T2, dim2...> v2);

  template <class V, class U, int...dim>
  friend std::enable_if_t<
    not is_Matrix_v<U>,
    Matrix<typename std::invoke_result_t<std::divides<>, V, U>, dim...>
  >
  operator/(Matrix<V, dim...> m, U scalar);

  template <class T1, int... dim, class T2>
  friend Matrix<typename std::invoke_result_t<std::divides<>, T1, T2>, dim...>
  operator/(Matrix<T1, dim...> v1, Matrix<T2, dim...> v2);

  template <class V, class U, int...dim>
  friend std::enable_if_t<
    not is_Matrix_v<U>,
    Matrix<typename std::invoke_result_t<std::plus<>, U, V>, dim...>
  >
  operator+(U scalar, Matrix<V, dim...> m);

  template <class V, class U, int...dim>
  friend Matrix<typename std::invoke_result_t<std::plus<>, V, U>, dim...>
  operator+(Matrix<V, dim...> m, U scalar);

  template <class T1, int... dim, class T2>
  friend Matrix<typename std::invoke_result_t<std::plus<>, T1, T2>, dim...>
  operator+(Matrix<T1, dim...> v1, Matrix<T2, dim...> v2);

  template <class V, class U, int...dim>
  friend std::enable_if_t<
    not is_Matrix_v<U>,
    Matrix<typename std::invoke_result_t<std::minus<>, V, U>, dim...>
  >
  operator-(Matrix<V, dim...> m, U scalar);

  template <class T1, int... dim, class T2>
  friend Matrix<typename std::invoke_result_t<std::minus<>, T1, T2>, dim...>
  operator-(Matrix<T1, dim...> v1, Matrix<T2, dim...> v2);

  template <class U>
  typename std::invoke_result_t<std::plus<>,
    typename std::invoke_result_t<std::multiplies<>, T, U>,
    typename std::invoke_result_t<std::multiplies<>, T, U>
  >
    dot(const Matrix<U, first>& m);

  friend bool operator== <> (const Matrix<T, first>& m1, const Matrix<T, first> m2);
  friend bool operator!= <>(const Matrix<T, first>& m1, const Matrix<T, first> m2);
  friend bool operator<= <>(const Matrix<T, first>& m1, const Matrix<T, first> m2);
  friend bool operator>= <>(const Matrix<T, first>& m1, const Matrix<T, first> m2);
  friend bool operator< <>(const Matrix<T, first>& m1, const Matrix<T, first> m2);
  friend bool operator> <>(const Matrix<T, first>& m1, const Matrix<T, first> m2);

  template <class U, int... dim>
  friend class Matrix;

  template <int... dim>
  Matrix<T, dim...> operator[](const std::string& selector);

  template <class Functor>
  Matrix<typename std::invoke_result_t<Functor, T>, first> generate(Functor generator);
};

template <int first, int... rest>
class Matrix<bool, first, rest...> {

  int _data[std::min(first * (rest * ...) / sizeof(int) / 8, 1)];

public:

  using list_form = std::initializer_list<
                      typename Matrix<bool, rest...>::list_form
                    >;

  Matrix();
  Matrix(list_form data) {
    if (data.size() != first) {
      throw std::length_error("Received " + std::to_string(data.size()) + 
                              " element for a dimension of " + std::to_string(first));
    }
  }

  /**
   *  @todo add static requirements for bool conversion
   */
  template <class U>
  Matrix(const Matrix<U, first, rest...>& m);
  
  friend std::ostream& operator<< <>(std::ostream& os, const Matrix<bool, first, rest...>& m);

  template <int... dim>
  Matrix<bool, dim...> operator[](const std::string& selector);

  template <class Functor>
  Matrix<typename std::invoke_result_t<Functor, bool>, first, rest...> generate(Functor generator);

  template <class U, int... dim>
  friend class Matrix;

  bool allTrue() const;
  bool allFalse() const;
  bool someTrue() const;
  bool someFalse() const;

  template <int... dim>
  friend Matrix<bool, dim...>
  operator and(const Matrix<bool, dim...>& m1, const Matrix<bool, dim...>& m2);

  template <int... dim>
  friend Matrix<bool, dim...>
  operator or(const Matrix<bool, dim...>& m1, const Matrix<bool, dim...>& m2);

  template <int... dim>
  friend Matrix<bool, dim...>
  operator not(const Matrix<bool, dim...>& m);

  template<int... dim>
  friend Matrix<bool, dim...>
  operator xor(const Matrix<bool, dim...>& m1, const Matrix<bool, dim...>& m2);

};

template <int first>
class Matrix<bool, first> {

  int _data[std::min(first / int(sizeof(int)) / 8, 1)];

public:

  using list_form = std::initializer_list<bool>;

  Matrix();
  Matrix(list_form data) {
    if (data.size() != first) {
      throw std::length_error("Received " + std::to_string(data.size()) + 
                              " element for a dimension of " + std::to_string(first));
    }
  }

  /**
   *  @todo add static requirements for bool conversion
   */
  template <class U>
  Matrix(const Matrix<U, first>& m);
  
  friend std::ostream& operator<< <>(std::ostream& os, const Matrix<bool, first>& m);

  template <int dim>
  Matrix<bool, dim> operator[](const std::string& selector);

  template <class Functor>
  Matrix<typename std::invoke_result_t<Functor, bool>, first> generate(Functor generator);

  template <class U, int... dim>
  friend class Matrix;

  bool allTrue() const;
  bool allFalse() const;
  bool someTrue() const;
  bool someFalse() const;

  template <int... dim>
  friend Matrix<bool, dim...>
  operator and(const Matrix<bool, dim...>& m1, const Matrix<bool, dim...>& m2);

  template <int... dim>
  friend Matrix<bool, dim...>
  operator or(const Matrix<bool, dim...>& m1, const Matrix<bool, dim...>& m2);

  template <int... dim>
  friend Matrix<bool, dim...>
  operator not(const Matrix<bool, dim...>& m);

  template<int... dim>
  friend Matrix<bool, dim...>
  operator xor(const Matrix<bool, dim...>& m1, const Matrix<bool, dim...>& m2);

};

typedef Matrix<double, 2> Vector;

#include "Matrix.ops.hpp"
