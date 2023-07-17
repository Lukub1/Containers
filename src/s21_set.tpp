using namespace s21;

template <typename T>
typename set<T>::Node *set<T>::insert(Node *node, const T &value,
                                      Node *parent) {
  if (node == nullptr) {
    node = new Node(value, parent);
    ++size_;
  } else if (value < node->value) {
    node->left = insert(node->left, value, node);
  } else if (value > node->value) {
    node->right = insert(node->right, value, node);
  }
  return node;
}

template <typename T>
typename set<T>::Node *set<T>::remove(Node *node, const T &value) {
  if (node == nullptr) {
    return nullptr;
  } else if (value < node->value) {
    node->left = remove(node->left, value);
  } else if (value > node->value) {
    node->right = remove(node->right, value);
  } else {
    if (node->left == nullptr && node->right == nullptr) {
      delete node;
      node = nullptr;
      --size_;
    } else if (node->left == nullptr) {
      Node *temp = node;
      node = node->right;
      node->parent = temp->parent;
      delete temp;
      --size_;
    } else if (node->right == nullptr) {
      Node *temp = node;
      node = node->left;
      node->parent = temp->parent;
      delete temp;
      --size_;
    } else {
      Node *successor = findLeftmost(node->right);
      node->value = successor->value;
      node->right = remove(node->right, successor->value);
    }
  }
  return node;
}

template <typename T>
typename set<T>::Node *set<T>::find(Node *node, const T &value) const {
  if (node == nullptr || node->value == value) {
    return node;
  } else if (value < node->value) {
    return find(node->left, value);
  } else {
    return find(node->right, value);
  }
}

template <typename T>
void set<T>::swap(set &other) {
  std::swap(root, other.root);
  std::swap(size_, other.size_);
}

template <typename T>
void set<T>::merge(set &other) {
  set<T>::Iterator it = other.begin();
  for (int i = 0; i < other.size(); i++) {
    insert(*it);
    ++it;
  }
  other.clear();
}

template <typename T>
void set<T>::clear(Node *node) {
  if (node != nullptr) {
    clear(node->left);
    clear(node->right);
    delete node;
  }
}

template <typename T>
set<T>::set(std::initializer_list<T> const &items) : set() {
  for (const T &item : items) {
    insert(item);
  }
}

template <typename T>
set<T>::set(const set &other) : set() {
  for (const T &item : other) {
    insert(item);
  }
}

template <typename T>
set<T>::set(set &&other) noexcept : root(other.root), size_(other.size_) {
  other.root = nullptr;
  other.size_ = 0;
}

template <typename T>
set<T>::~set() {
  clear();
}

template <typename T>
set<T> &set<T>::operator=(const set &other) {
  if (this != &other) {
    clear();
    for (const T &item : other) {
      insert(item);
    }
  }
  return *this;
}

template <typename T>
set<T> &set<T>::operator=(set &&other) noexcept {
  if (this != &other) {
    clear();
    root = other.root;
    size_ = other.size_;
    other.root = nullptr;
    other.size_ = 0;
  }
  return *this;
}

template <typename T>
void set<T>::insert(const T &value) {
  root = insert(root, value, nullptr);
}

template <typename T>
void set<T>::erase(const T &value) {
  root = remove(root, value);
}

template <typename T>
bool set<T>::contains(const T &value) const {
  return find(root, value) != nullptr;
}

template <typename T>
int set<T>::count(const T &value) const {
  return contains(value) ? 1 : 0;
}

template <typename T>
void set<T>::clear() {
  clear(root);
  root = nullptr;
  size_ = 0;
}

template <typename T>
int set<T>::size() const {
  return size_;
}

template <typename T>
bool set<T>::empty() const {
  return size_ == 0;
}

template <typename T>
typename set<T>::Node *set<T>::findRightmost(Node *node) {
  if (node == nullptr) {
    return nullptr;
  }
  while (node->right != nullptr) {
    node = node->right;
  }
  return node;
}

template <typename T>
typename set<T>::Node *set<T>::findLeftmost(Node *node) {
  if (node == nullptr) {
    return nullptr;
  }
  while (node->left != nullptr) {
    node = node->left;
  }
  return node;
}

template <typename T>
typename set<T>::Iterator set<T>::begin() {
  return Iterator(findLeftmost(root));
}

template <typename T>
typename set<T>::Iterator set<T>::end() {
  return Iterator(findRightmost(root));
}

template <typename T>
typename set<T>::ConstIterator set<T>::begin() const {
  return ConstIterator(findLeftmost(root));
}

template <typename T>
typename set<T>::ConstIterator set<T>::end() const {
  return ConstIterator(nullptr, root);
}

template <typename T>
set<T>::Iterator::Iterator(Node *root)
    : current(findLeftmost(root)), treeRoot(root) {}

template <typename T>
bool set<T>::Iterator::operator!=(const Iterator &other) const {
  return current != other.current;
}

template <typename T>
typename set<T>::Iterator &set<T>::Iterator::operator++() {
  if (current == nullptr) {
    current = findLeftmost(treeRoot);
  } else if (current->right != nullptr) {
    current = findLeftmost(current->right);
  } else {
    while (current != nullptr && current->parent != nullptr &&
           current == current->parent->right) {
      current = current->parent;
    }
    if (current == nullptr) {
      return *this;
    }
    current = current->parent;
  }
  return *this;
}

template <typename T>
typename set<T>::Iterator set<T>::find(const T &value) {
  Node *node = find(root, value);
  return Iterator(node);
}

template <typename T>
typename set<T>::Iterator &set<T>::Iterator::operator--() {
  Node *prev = current;
  if (current == nullptr) {
    return *this;
  }
  if (current->left && current->left != prev) {
    current = current->left;
    while (current->right != nullptr) current = current->right;
  } else {
    current = current->parent;
    while (prev->value <= current->value) {
      if (current->left && current->left != prev) {
        current = current->left;
        while (current->right != nullptr) current = current->right;
      } else {
        while (prev->value <= current->value) {
          current = current->parent;
          if (current == nullptr) {
            break;
          }
        }
        break;
      }
    }
  }
  return *this;
}

template <typename T>
const T &set<T>::Iterator::operator*() const {
  return current->value;
}

template <typename T>
const T *set<T>::Iterator::operator->() const {
  return &(current->value);
}

template <typename T>
set<T>::ConstIterator::ConstIterator(Node *root)
    : current(findLeftmost(root)), treeRoot(root) {}

template <typename T>
set<T>::ConstIterator::ConstIterator(const Node *root)
    : current(findLeftmost(const_cast<Node *>(root))),
      treeRoot(const_cast<Node *>(root)) {}

template <typename T>
set<T>::ConstIterator::ConstIterator(Node *current, Node *treeRoot)
    : current(current), treeRoot(treeRoot) {}

template <typename T>
bool set<T>::ConstIterator::operator!=(const ConstIterator &other) const {
  return current != other.current;
}

template <typename T>
typename set<T>::ConstIterator &set<T>::ConstIterator::operator++() {
  if (current == nullptr) {
    current = findLeftmost(const_cast<Node *>(treeRoot));
  } else if (current->right != nullptr) {
    current = findLeftmost(const_cast<Node *>(current->right));
  } else {
    while (current != nullptr && current->parent != nullptr &&
           current == current->parent->right) {
      current = current->parent;
    }
    if (current == nullptr) {
      return *this;
    }
    current = current->parent;
  }
  return *this;
}

template <typename T>
typename set<T>::ConstIterator &set<T>::ConstIterator::operator--() {
  if (current == nullptr) {
    current = findRightmost(const_cast<Node *>(treeRoot));
  } else if (current->left != nullptr) {
    current = findRightmost(const_cast<Node *>(current->left));
  } else {
    const Node *prev = current;
    while (current != nullptr && current->left == prev) {
      prev = current;
      current = current->parent;
    }
  }
  return *this;
}

template <typename T>
const T &set<T>::ConstIterator::operator*() const {
  return current->value;
}

template <typename T>
const T *set<T>::ConstIterator::operator->() const {
  return &(current->value);
}
