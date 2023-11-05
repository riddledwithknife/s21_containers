#ifndef S21_QUEUE_H
#define S21_QUEUE_H

#include <initializer_list>
#include <utility>

#include "s21_list.h"

namespace s21 {
template <class T>
class queue {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const value_type &;
  using size_type = size_t;

  queue() : data() {}

  queue(std::initializer_list<value_type> const &items) : data(items) {}

  queue(const queue &q) : data(q.data) {}

  queue(queue &&q) noexcept : data(std::move(q.data)) {}

  ~queue() { data.clear(); }

  queue &operator=(queue &&q) noexcept {
    if (this != &q) {
      data = std::move(q.data);
    }
    return *this;
  }

  // Element access
  const_reference front() { return data.front(); }

  const_reference back() { return data.back(); }

  // Capacity
  bool empty() { return data.empty(); }

  size_type size() { return data.size(); }

  // Modifiers
  void push(const_reference value) { data.push_back(value); }

  void pop() { data.pop_front(); }

  void swap(queue &other) { data.swap(other.data); }

 private:
  s21::list<value_type> data;
};
}  // namespace s21

#endif  // S21_QUEUE_H
