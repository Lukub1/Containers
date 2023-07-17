#ifndef CPP2_S21_CONTAINERS_1_S21_MAP_H
#define CPP2_S21_CONTAINERS_1_S21_MAP_H

#include <iostream>
#include <limits>
#include <stdexcept>
namespace s21 {
template <typename K, typename V>
class map {
 private:
  struct Node {
    K first;
    V second;
    Node *left;
    Node *right;
    Node *parent;

    Node(K key, V value, Node *node)
        : first(key),
          second(value),
          left(nullptr),
          right(nullptr),
          parent(node) {}
  };

  using key_type = K;
  using mapped_type = V;
  using value_type = std::pair<key_type, mapped_type>;
  using size_type = size_t;

  Node *root = nullptr;
  Node *insert(Node *node, K key, V value, Node *parent);
  Node *remove(Node *node, K key);
  Node *search(Node *node, K key) const;
  void clear(Node *node);
  int count(Node *node, K key);
  int size(Node *node);
  bool empty(Node *node);
  Node *begin(Node *node);
  Node *end(Node *node);
  void copyTree(const Node *srcNode, Node *srcParent, Node *&destNode);
  int size_ = 0;
  void updateParentPointers(Node *node);

 public:
  map() : root(nullptr) {}
  map(map &&other) noexcept;
  map(std::initializer_list<value_type> initList);
  map(const map &mp);
  ~map();
  void insert(K key, V value);
  void erase(K key);
  bool contains(K key) const;
  const V &operator[](K key) const;
  V &at(K key);
  V &at(K key, V value);
  V &operator[](K key);
  int count(K key);
  int size();
  size_type max_size();
  bool empty();
  Node *begin();
  Node *end();
  void swap(map &other);
  void merge(map &other);
  map<K, V> &operator=(map &&other) noexcept;

  class Iterator {
   private:
    Node *current;
    Node *treeRoot;
    Node *findLeftmost(Node *node);

   public:
    Iterator(Node *root);
    bool operator!=(const Iterator &other) const;
    Iterator &operator++(int);
    Iterator &operator--(int);
    Iterator &operator--();
    const Node &operator*() const;
    const Node *operator->() const;
    Iterator &operator=(const Iterator &other) const;

   private:
    Node *find(Node *node, const K &key);
  };

 public:
  std::pair<typename map<K, V>::Iterator, bool> insert(const value_type &value);
  template <typename... Args>
  std::pair<typename map<K, V>::Iterator, bool> emplace(Args &&...args);
};

#include "s21_map.tpp"
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_S21_MAP_H
