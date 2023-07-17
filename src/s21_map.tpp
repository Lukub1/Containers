using namespace s21;

template <typename K, typename V>
typename map<K, V>::Node *map<K, V>::insert(Node *node, K key, V value,
                                            Node *parent) {
  if (node == nullptr) {
    size_++;
    return new Node(key, value, parent);
  }
  if (key < node->first) {
    node->left = insert(node->left, key, value, node);
  } else if (key > node->first) {
    node->right = insert(node->right, key, value, node);

  } else {
    node->second = value;
  }
  return node;
}

template <typename K, typename V>
void map<K, V>::insert(K key, V value) {
  root = insert(root, key, value, nullptr);
}

template <typename K, typename V>
typename map<K, V>::Node *map<K, V>::remove(Node *node, K key) {
  if (node == nullptr) {
    return nullptr;
  }
  if (key == node->first) {
    Node *temp;
    if (node->left == nullptr && node->right == nullptr) {
      delete node;
      size_--;
      return nullptr;
    } else if (node->left == nullptr) {
      temp = node->right;
      delete node;
      size_--;
      return temp;
    } else if (node->right == nullptr) {
      temp = node->left;
      delete node;
      size_--;
      return temp;
    } else {
      temp = node->right;
      while (temp->left != nullptr) {
        temp = temp->left;
      }
      node->first = temp->first;
      node->second = temp->second;
      node->right = remove(node->right, temp->first);
      return node;
    }
  } else if (key < node->first) {
    node->left = remove(node->left, key);
  } else {
    node->right = remove(node->right, key);
  }
  return node;
}

template <typename K, typename V>
void map<K, V>::erase(K key) {
  if (key == root->first) {
    root = remove(root, key);
  } else {
    remove(root, key);
  }
}

template <typename K, typename V>
typename map<K, V>::Node *map<K, V>::search(Node *node, K key) const {
  if (node == nullptr) {
    return nullptr;
  }
  if (key < node->first) {
    return search(node->left, key);
  } else if (key > node->first) {
    return search(node->right, key);
  } else {
    return node;
  }
}

template <typename K, typename V>
map<K, V>::map(const map &other) : root(nullptr) {
  if (other.root != nullptr) {
    copyTree(other.root, nullptr, root);
  }
}

template <typename K, typename V>
void map<K, V>::copyTree(const Node *srcNode, Node *srcParent,
                         Node *&destNode) {
  if (srcNode == nullptr) {
    destNode = nullptr;
    return;
  }
  destNode = new Node(srcNode->first, srcNode->second, srcParent);
  copyTree(srcNode->left, destNode, destNode->left);
  copyTree(srcNode->right, destNode, destNode->right);
}

template <typename K, typename V>
map<K, V>::map(map &&other) noexcept : root(nullptr) {
  root = other.root;
  other.root = nullptr;
}

template <typename K, typename V>
map<K, V>::map(std::initializer_list<value_type> initList) : root(nullptr) {
  for (const auto &pair : initList) {
    insert(pair.first, pair.second);
  }
}

template <typename K, typename V>
map<K, V>::~map() {
  clear(root);
  root = nullptr;
  size_ = 0;
}

template <typename K, typename V>
void map<K, V>::clear(Node *node) {
  if (node != nullptr) {
    clear(node->left);
    clear(node->right);
    delete node;
  }
}

template <typename K, typename V>
bool map<K, V>::contains(K key) const {
  return search(root, key) != nullptr;
}

template <typename K, typename V>
V &map<K, V>::at(K key) {
  if (!(this->contains(key))) {
    throw std::out_of_range("Key not found");
  } else {
    Node *node = search(root, key);
    return node->second;
  }
}

template <typename K, typename V>
V &map<K, V>::operator[](K key) {
  return at(key);
}

template <typename K, typename V>
int map<K, V>::count(Node *node, K key) {
  return search(node, key) ? 1 : 0;
}

template <typename K, typename V>
int map<K, V>::count(K key) {
  return count(root, key);
}

template <typename K, typename V>
int map<K, V>::size(Node *node) {
  int size_m = 0;
  if (node == nullptr) {
    return 0;
  }
  size_m += size(node->left);
  size_m += size(node->right);
  size_m++;
  return size_m;
}

template <typename K, typename V>
int map<K, V>::size() {
  return size(root);
}

template <typename K, typename V>
typename s21::map<K, V>::size_type s21::map<K, V>::max_size() {
  return std::numeric_limits<size_type>::max();
}

template <typename K, typename V>
bool map<K, V>::empty() {
  return (root == nullptr) ? true : false;
}

template <typename K, typename V>
void map<K, V>::swap(map &other) {
  std::swap(root, other.root);
}

template <typename K, typename V>
void s21::map<K, V>::merge(map &other) {
  s21::map<K, V>::Iterator it = other.begin();
  for (int i = 0; i < other.size(); i++) {
    insert(it->first, it->second);
    it++;
  }
  other.~map();
}

template <typename K, typename V>
map<K, V> &map<K, V>::operator=(map &&other) noexcept {
  if (this != &other) {
    clear(root);
    root = other.root;
    other.root = nullptr;
    if (root != nullptr) {
      root->parent = nullptr;
      updateParentPointers(root);
    }
  }
  return *this;
}

template <typename K, typename V>
void map<K, V>::updateParentPointers(Node *node) {
  if (node == nullptr) {
    return;
  }
  if (node->left != nullptr) {
    node->left->parent = node;
    updateParentPointers(node->left);
  }
  if (node->right != nullptr) {
    node->right->parent = node;
    updateParentPointers(node->right);
  }
}

template <typename K, typename V>
typename map<K, V>::Node *map<K, V>::Iterator::findLeftmost(Node *node) {
  while (node && node->left != nullptr) {
    node = node->left;
  }
  return node;
}

template <typename K, typename V>
map<K, V>::Iterator::Iterator(s21::map<K, V>::Node *root)
    : current(nullptr), treeRoot(root) {
  current = root;
}

template <typename K, typename V>
bool map<K, V>::Iterator::operator!=(
    const s21::map<K, V>::Iterator &other) const {
  return current != other.current;
}

template <typename K, typename V>
typename map<K, V>::Iterator &map<K, V>::Iterator::operator++(int) {
  Node *prev = current;
  if (current == nullptr) {
    return *this;
  }
  if (current->right && current->right != prev) {
    current = current->right;
    while (current->left != nullptr) current = current->left;

  } else {
    current = current->parent;
    while (prev->first >= current->first) {
      if (current->right && current->right != prev) {
        current = current->right;
        while (current->left != nullptr) current = current->left;
      } else {
        if (prev->first >= current->first) {
          current = current->parent;
        }
        break;
      }
    }
  }
  return *this;
}

template <typename K, typename V>
typename map<K, V>::Iterator &map<K, V>::Iterator::operator--() {
  return operator--();
}

template <typename K, typename V>
typename map<K, V>::Iterator &map<K, V>::Iterator::operator--(int) {
  Node *prev = current;
  if (current == nullptr) {
    return *this;
  }
  if (current->left && current->left != prev) {
    current = current->left;
    while (current->right != nullptr) current = current->right;
  } else {
    current = current->parent;
    while (prev->first <= current->first) {
      if (current->left && current->left != prev) {
        current = current->left;
        while (current->right != nullptr) current = current->right;
      } else {
        while (prev->first <= current->first) {
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

template <typename K, typename V>
const typename map<K, V>::Node &map<K, V>::Iterator::operator*() const {
  if (map<K, V>::Iterator::current == nullptr) {
    throw std::runtime_error("Dereferencing null iterator");
  }
  return *map<K, V>::Iterator::current;
}

template <typename K, typename V>
const typename map<K, V>::Node *map<K, V>::Iterator::operator->() const {
  return current;
}

template <typename K, typename V>
typename map<K, V>::Node *map<K, V>::begin(Node *node) {
  while (node && node->left) {
    node = node->left;
  }
  return node;
}

template <typename K, typename V>
typename map<K, V>::Node *map<K, V>::begin() {
  return begin(root);
}

template <typename K, typename V>
typename map<K, V>::Node *map<K, V>::end(Node *node) {
  while (node && node->right) {
    node = node->right;
  }
  return node;
}

template <typename K, typename V>
typename map<K, V>::Node *map<K, V>::end() {
  return end(root);
}

template <typename K, typename V>
typename map<K, V>::Iterator end() {
  return map<K, V>::Iterator(nullptr);
}

template <typename K, typename V>
typename map<K, V>::Node map<K, V>::Iterator::*find(
    typename map<K, V>::Node *node, const K &key) {
  if (node == nullptr || node->first == key) {
    return node;
  }
  if (key < node->first) {
    return find(node->left, key);
  } else {
    return find(node->right, key);
  }
}

template <typename K, typename V>
std::pair<typename map<K, V>::Iterator, bool> map<K, V>::insert(
    const value_type &value) {
  Node *parent = nullptr;
  Node *current = root;
  while (current != nullptr) {
    parent = current;
    if (value.first < current->first) {
      current = current->left;
    } else if (value.first > current->first) {
      current = current->right;
    } else {
      return std::make_pair(Iterator(current), false);
    }
  }
  Node *newNode = new Node(value.first, value.second, parent);
  if (parent == nullptr) {
    root = newNode;
  } else if (value.first < parent->first) {
    parent->left = newNode;
  } else {
    parent->right = newNode;
  }
  return std::make_pair(Iterator(newNode), true);
}

template <typename K, typename V>
template <typename... Args>
std::pair<typename map<K, V>::Iterator, bool> map<K, V>::emplace(
    Args &&...args) {
  Node *newNode = new Node(std::forward<Args>(args)...);
  if (root == nullptr) {
    root = newNode;
  } else {
    Node *currentNode = root;
    Node *parent = nullptr;
    while (currentNode != nullptr) {
      parent = currentNode;

      if (newNode->key < currentNode->key) {
        currentNode = currentNode->left;
      } else if (newNode->key > currentNode->key) {
        currentNode = currentNode->right;
      } else {
        delete newNode;
        return std::make_pair(Iterator(currentNode), false);
      }
    }
    if (newNode->key < parent->key) {
      parent->left = newNode;
    } else {
      parent->right = newNode;
    }

    newNode->parent = parent;
  }
  size_++;
  return std::make_pair(Iterator(newNode), true);
}
