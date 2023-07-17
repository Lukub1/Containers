using namespace s21;

template <class T>
list<T>::list() : head_(nullptr), tail_(nullptr) {}

template <class T>
list<T>::list(size_type n) : size_(n), head_(nullptr), tail_(nullptr) {}

template <class T>
[[nodiscard]] list<T>::list(std::initializer_list<T> const &items)
    : size_(0), head_(nullptr), tail_(nullptr) {
  for (auto &it : items) this->push_back(it);
};

template <class T>
list<T>::list(const list &other) : size_(0), head_(nullptr), tail_(nullptr) {
  Node *tmp = other.head_;
  while (tmp) {
    push_back(tmp->data);
    tmp = tmp->next;
  }
};

template <class T>
list<T>::list(list &&other) : size_(0), head_(nullptr), tail_(nullptr) {
  this->swap(other);
};

template <class T>
list<T>::~list() {
  if (head_ != nullptr) {
    Node *temp;
    temp = head_;
    while (temp != nullptr) {
      head_->next = nullptr;
      temp = head_->prev;
      head_->prev = nullptr;
      delete head_;
      head_ = temp;
    }
    head_ = nullptr;
  }
};

template <class T>
list<T> &list<T>::operator=(list &&other) {
  this->swap(other);
  return *this;
};

// List Element access

// access the head_ element
template <class T>
typename list<T>::const_reference list<T>::front() {
  return (head_->data);
};

// access the tail_ element
template <class T>
typename list<T>::const_reference list<T>::back() {
  return (tail_->data);
};

// List Iterators

// returns an iterator to the beginning
template <class T>
typename list<T>::iterator list<T>::begin() {
  return ListIterator(head_);
};
template <class T>
typename list<T>::const_iterator list<T>::beginConst() {
  return ListConstIterator(head_);
};

template <class T>
T list<T>::ListIterator::operator*() {
  return iter_ ? iter_->data : 0;
};

template <class T>
T list<T>::ListConstIterator::operator*() {
  return iter_ ? iter_->data : 0;
};

template <class T>
void list<T>::ListIterator::operator++() {
  if (iter_) iter_ = iter_->next;
};
template <class T>
void list<T>::ListConstIterator::operator++() {
  if (iter_) iter_ = iter_->next;
};

template <class T>
bool list<T>::ListIterator::operator==(const ListIterator &other) {
  return iter_ == other.iter_;
};

template <class T>
bool list<T>::ListConstIterator::operator==(const ListConstIterator &other) {
  return iter_ == other.iter_;
};
template <class T>
bool list<T>::ListIterator::operator!=(const ListIterator &other) {
  return iter_ != other.iter_;
};
template <class T>
bool list<T>::ListConstIterator::operator!=(const ListConstIterator &other) {
  return iter_ != other.iter_;
};
// returns an iterator to the end
template <class T>
typename list<T>::iterator list<T>::end() {
  iterator buf(tail_);
  ++buf;
  return buf;
};
template <class T>
typename list<T>::const_iterator list<T>::endConst() {
  const_iterator buf(tail_);
  ++buf;
  return buf;
};

// List Capacity
template <class T>
bool list<T>::empty() {
  return head_ == nullptr;
};

template <class T>
typename list<T>::size_type list<T>::size() {
  return size_;
};

template <class T>
typename list<T>::size_type list<T>::max_size() {
  return static_cast<size_type>(pow(2, sizeof(void *) * 8) / sizeof(list) - 1);
};

// List Modifiers
template <class T>
void list<T>::clear() {
  while (head_) {
    tail_ = head_->next;
    delete head_;
    head_ = tail_;
  }
  size_ = 0;
};

template <class T>
typename list<T>::iterator list<T>::insert(iterator pos,
                                           const_reference value) {
  if (pos == end()) {
    push_back(value);
  } else if (pos == begin()) {
    push_front(value);
  } else {
    ++size_;
    Node *buf = new Node;
    Node *it = pos.iter_;
    buf->data = value;
    buf->prev = it->prev;
    buf->next = it;
    if (it->prev) it->prev->next = buf;
    it->prev = buf;
    pos.iter_ = buf;
  }
  return pos;
};

template <class T>
void list<T>::insertConst(const_iterator pos, const_reference value) {
  if (pos == endConst()) {
    push_back(value);
  } else if (pos == beginConst()) {
    push_front(value);
  } else {
    ++size_;
    Node *buf = new Node;
    Node *it = pos.iter_;
    buf->data = value;
    buf->prev = it->prev;
    buf->next = it;
    if (it->prev) it->prev->next = buf;
    it->prev = buf;
    pos.iter_ = buf;
  }
};

template <class T>
void list<T>::erase(iterator pos) {
  if (pos.iter_ == nullptr) {
    throw std::out_of_range("Incorrect iterator");
  } else {
    size_--;
    if (pos.iter_ == head_) head_ = pos.iter_->next;
    if (pos.iter_ == tail_) tail_ = pos.iter_->prev;
    if (pos.iter_->prev) pos.iter_->prev->next = pos.iter_->next;
    if (pos.iter_->next) pos.iter_->next->prev = pos.iter_->prev;
    delete pos.iter_;
    pos.iter_ = nullptr;
  }
};

template <class T>
void list<T>::push_back(const_reference value) {
  size_++;
  Node *buf = new Node;
  buf->data = value;
  buf->prev = tail_;
  buf->next = nullptr;
  if (tail_ != nullptr) {
    tail_->next = buf;
  }
  tail_ = buf;
  if (head_ == nullptr) {
    head_ = buf;
  }
};

template <class T>
void list<T>::pop_back() {
  if (tail_ != nullptr) {
    size_--;
    Node *buf = tail_->prev;
    delete tail_;
    tail_ = buf;
    tail_->next = nullptr;
  };
};

template <class T>
void list<T>::push_front(const_reference value) {
  size_++;
  Node *buf = new Node;
  buf->data = value;
  buf->prev = nullptr;
  buf->next = head_;
  if (head_ != nullptr) {
    head_->prev = buf;
  }
  head_ = buf;
  if (tail_ == nullptr) {
    tail_ = buf;
  }
};

template <class T>
void list<T>::pop_front() {
  if (head_ != nullptr) {
    head_ = head_->next;
    if (head_ != nullptr) {
      head_->prev = nullptr;
    }
    size_--;
  }
};

template <class T>
void list<T>::swap(list &other) {
  std::swap(head_, other.head_);
  std::swap(tail_, other.tail_);
  std::swap(size_, other.size_);
};

template <class T>
void list<T>::merge(list &other) {
  const_iterator it = endConst();
  this->splice(it, other);
  sort();
};

template <class T>
void list<T>::splice(const_iterator pos, list &other) {
  iterator it = other.begin();
  for (size_t i = 0; i < other.size(); ++i) {
    insertConst(pos, *it);
    ++it;
  }
  other.clear();
};

template <class T>
void list<T>::reverse() {
  if (size_ < 2) {
    return;
  }
  s21::list<T> tmp(0);
  for (Node *it_i = head_; it_i != nullptr; it_i = it_i->next) {
    tmp.push_front(it_i->data);
  }
  for (Node *it_i = head_, *it_j = tmp.head_; it_i != nullptr;
       it_i = it_i->next, it_j = it_j->next) {
    it_i->data = it_j->data;
  }
};

template <class T>
void list<T>::unique() {
  if (size_ < 2) {
    return;
  }
  for (iterator it_i = begin(); it_i != end(); ++it_i) {
    iterator it_k = it_i;
    ++it_k;
    for (iterator it_j = it_k; it_j != end(); ++it_j) {
      if (it_i.iter_->data == it_j.iter_->data) this->erase(it_j);
    };
  };
};

template <class T>
void list<T>::sort() {
  if (size_ < 2) {
    return;
  }
  value_type tmp;

  for (Node *it_i = head_; it_i != nullptr; it_i = it_i->next) {
    for (Node *it_j = head_; it_j != nullptr; it_j = it_j->next) {
      if (it_j->data > it_i->data) {
        tmp = it_j->data;
        it_j->data = it_i->data;
        it_i->data = tmp;
      }
    }
  }
}
template <class T>
void list<T>::print() {
  if (empty()) return;
  Node *p = head_;
  while (p) {
    std::cout << p->data << ", ";
    p = p->next;
  }
  std::cout << std::endl;
}