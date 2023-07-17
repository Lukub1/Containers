// #pragma once
#ifndef SRC_S21_LIST_H_
#define SRC_S21_LIST_H_
#include <cmath>
#include <iostream>

namespace s21 {
template <class T>
class list {
 public:
  struct Node {
    T data;
    Node *prev;
    Node *next;
  };
  class ListIterator {
    friend class list;

   public:
    ListIterator() { iter_ = nullptr; }
    explicit ListIterator(Node *node) { iter_ = node; }
    T operator*();
    void operator++();
    bool operator==(const ListIterator &other);
    bool operator!=(const ListIterator &other);

   private:
    Node *iter_;
  };

  class ListConstIterator {
    friend class list;

   public:
    ListConstIterator() { iter_ = nullptr; }
    explicit ListConstIterator(Node *node) { iter_ = node; }
    T operator*();
    void operator++();
    bool operator==(const ListConstIterator &other);
    bool operator!=(const ListConstIterator &other);

   private:
    Node *iter_;
  };

  // List Member type
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = ListIterator;
  using const_iterator = ListConstIterator;
  using size_type = size_t;

  // List Functions
  list();
  explicit list(size_type n);
  explicit list(std::initializer_list<value_type> const &items);
  list(const list &other);
  list(list &&other);
  ~list();
  list &operator=(list &&other);
  // List Element access
  const_reference front();
  const_reference back();
  // List Iterators
  iterator begin();
  const_iterator beginConst();
  iterator end();
  const_iterator endConst();
  // List Capacity
  bool empty();
  size_type size();
  size_type max_size();
  // List Modifiers
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(list &other);
  void merge(list &other);
  void splice(const_iterator pos, list &other);
  void reverse();
  void unique();
  void sort();
  void insertConst(const_iterator pos, const_reference value);
  void print();  // TODO delete

 private:
  size_t size_;
  Node *head_;
  Node *tail_;
};
#include "s21_list.tpp"
};      // namespace s21
#endif  //  SRC_S21_LIST_H_