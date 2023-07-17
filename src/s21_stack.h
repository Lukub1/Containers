#ifndef SRC_S21_STACK_H_
#define SRC_S21_STACK_H_

namespace s21 {
template <typename T>
class stack {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  stack() : stack_(){};
  stack(std::initializer_list<value_type> const &items) : stack_(items){};
  stack(const stack &s) : stack_(s.stack_){};
  stack(stack &&s) : stack_(std::move(s.stack_)){};
  ~stack() = default;

  void operator=(stack &&s) { std::move(s.stack_); };

  const_reference top() { return stack_.back(); };
  bool empty() { return stack_.empty(); };
  size_type size() { return stack_.size(); };
  void push(const_reference value) { stack_.push_back(value); };
  void pop() { stack_.pop_back(); };
  void swap(stack &other) { stack_.swap(other.stack_); };

 private:
  list<T> stack_;
};
}  // namespace s21
#endif  //  SRC_S21_STACK_H_