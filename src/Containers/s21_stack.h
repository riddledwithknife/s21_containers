#ifndef S21_STACK_H
#define S21_STACK_H

#include <initializer_list>
#include <stdexcept>
#include <utility>

#include "s21_list.h"

namespace s21 {
template <class T>
class stack {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const value_type &;
  using size_type = size_t;

  stack() = default;

  stack(std::initializer_list<value_type> const &items) {
    for (const auto &i : items) {
      push(i);
    }
  }

  stack(const stack &s) : data(s.data) {}

  stack(stack &&s) noexcept { data.swap(s.data); }

  ~stack() = default;

  stack &operator=(stack &&s) noexcept {
    if (this != &s) {
      data.swap(s.data);
    }
    return *this;
  }

  // Element access
  const_reference top() {
    if (empty()) {
      throw std::out_of_range("Stack is empty");
    }
    return data.front();
  }

  // Capacity
  bool empty() { return data.empty(); }

  size_type size() { return data.size(); }

  // Modifiers
  void push(const_reference value) { data.push_front(value); }

  void pop() {
    if (empty()) {
      throw std::out_of_range("Stack is empty");
    }
    data.pop_front();
  }

  void swap(stack &other) { data.swap(other.data); }

 private:
  s21::list<T> data;
};
}  // namespace s21

#endif  // S21_STACK_H
