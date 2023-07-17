#ifndef SRC_S21_QUEUE_H_
#define SRC_S21_QUEUE_H_

namespace s21 {
template <typename T>
class queue {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  queue() : queue_(){};
  queue(std::initializer_list<value_type> const &items) : queue_(items){};
  queue(queue &q) : queue_(q.queue_){};
  queue(queue &&q) : queue_(std::move(q.queue_)){};
  ~queue() = default;

  void operator=(queue &&q) { std::move(q); };

  const_reference front() { return queue_.front(); };
  const_reference back() { return queue_.back(); };

  bool empty() { return queue_.empty(); };
  size_type size() { return queue_.size(); };
  void push(const_reference value) { queue_.push_back(value); };
  void pop() { queue_.pop_front(); };
  void swap(queue &other) { queue_.swap(other.queue_); };

 private:
  list<T> queue_;
};
}  // namespace s21
#endif  //  SRC_S21_QUEUE_H_
