#ifndef S21_VECTOR_H
#define S21_VECTOR_H

#include <stdarg.h>

#include <cmath>
#include <iostream>

namespace s21 {

template <typename T>
class vector {
  typedef T value_type;
  typedef T &reference;
  typedef const T &const_reference;
  typedef T *iterator;
  typedef const T *const_iterator;
  typedef size_t size_type;

 private:
  value_type *arr;
  size_type m_size;
  size_type m_capacity;
  void destroy();

 public:
  vector();
  explicit vector(size_type n);
  vector(std::initializer_list<value_type> const &items);
  vector(const vector &v);
  vector(vector &&v);
  ~vector();
  vector &operator=(vector &&v);
  vector &operator=(const vector &v);

  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front() const;
  reference front();
  const_reference back() const;
  reference back();
  iterator data();

  iterator begin();
  const_iterator begin() const;
  iterator end();
  const_iterator end() const;

  bool empty();
  size_type size();
  size_type max_size();
  void reserve(size_type size);
  size_type capacity();
  void shrink_to_fit();

  void clear();

  template <typename iterator_type>
  iterator insert(iterator_type pos, const_reference value);

  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector &other);
};
#include "s21_vector.tpp"
}  // namespace s21

#endif  // S21_VECTOR_H
