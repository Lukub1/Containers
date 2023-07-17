#include <initializer_list>
#include <iostream>
#include <utility>

namespace s21 {

template <typename T>
class set {
 private:
  struct Node {
    T value;
    Node *left;
    Node *right;
    Node *parent;
    Node(const T &val, Node *parentNode)
        : value(val), left(nullptr), right(nullptr), parent(parentNode) {}
  };

  Node *root = nullptr;
  int size_ = 0;
  static Node *findLeftmost(Node *node);
  static Node *findRightmost(Node *node);
  Node *insert(Node *node, const T &value, Node *parent);
  Node *remove(Node *node, const T &value);
  Node *find(Node *node, const T &value) const;
  void clear(Node *node);

 public:
  using value_type = T;

  set() = default;
  set(std::initializer_list<T> const &items);
  set(const set &other);
  set(set &&other) noexcept;
  ~set();
  set &operator=(const set &other);
  set &operator=(set &&other) noexcept;
  void insert(const T &value);
  void erase(const T &value);
  bool contains(const T &value) const;
  int count(const T &value) const;
  void clear();
  int size() const;
  void swap(set &other);
  void merge(set &other);
  bool empty() const;

  class Iterator;
  class ConstIterator;

  Iterator begin();
  Iterator end();
  Iterator find(const T &value);
  ConstIterator begin() const;
  ConstIterator end() const;
};

template <typename T>
class set<T>::Iterator {
 private:
  Node *current;
  Node *treeRoot;

 public:
  Iterator(Node *root);
  bool operator!=(const Iterator &other) const;
  Iterator &operator++();
  Iterator &operator--();
  const T &operator*() const;
  const T *operator->() const;

  operator ConstIterator() const { return ConstIterator(current, treeRoot); }
};

template <typename T>
class set<T>::ConstIterator {
 private:
  Node *current;
  Node *treeRoot;

 public:
  ConstIterator(Node *root);
  ConstIterator(const Node *root);
  ConstIterator(Node *root, Node *treeRoot);
  bool operator!=(const ConstIterator &other) const;
  ConstIterator &operator++();
  ConstIterator &operator--();
  const T &operator*() const;
  const T *operator->() const;
};

#include "s21_set.tpp"

}  // namespace s21
