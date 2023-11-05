#ifndef S21_MAP_H
#define S21_MAP_H

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <utility>

#include "s21_binary_tree.h"

namespace s21 {
template <typename Key, typename T>
class map {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename RedBlackTree<value_type>::iterator;
  using const_iterator = typename RedBlackTree<value_type>::const_iterator;
  using size_type = size_t;

  map() noexcept = default;

  map(std::initializer_list<value_type> const &items) noexcept {
    for (const auto &item : items) {
      tree_.insert(item);
    }
  }

  map(const map &m) noexcept {
    for (const auto &pair : m) {
      tree_.insert(pair);
    }
  }

  map(map &&m) noexcept {
    tree_.clear();
    swap(m);
  }

  ~map() noexcept = default;

  map &operator=(map &&m) noexcept {
    if (this != &m) {
      tree_ = std::move(m.tree_);
    }

    return *this;
  }

  // Element access
  mapped_type &at(const key_type &key) const {
    iterator it = find(key);

    if (it == end()) {
      throw std::out_of_range("Key not found");
    }

    return (*it).second;
  }

  mapped_type &operator[](const key_type &key) const {
    iterator it = find(key);

    if (it == end()) {
      throw std::out_of_range("Key not found");
    }

    return (*it).second;
  }

  // Iterators
  iterator begin() const noexcept { return tree_.begin(); }

  iterator end() const noexcept { return tree_.end(); }

  // Capacity
  bool empty() const noexcept { return tree_.empty(); }

  size_type size() const noexcept { return tree_.size(); }

  size_type max_size() const noexcept { return tree_.max_size() / 2; }

  // Modifiers
  void clear() noexcept { tree_.clear(); }

  std::pair<iterator, bool> insert(const value_type &value) noexcept {
    iterator it = find(value.first);

    if (it != end()) {
      return {it, false};
    } else {
      return tree_.insert(value);
    }
  }

  std::pair<iterator, bool> insert(const key_type &key,
                                   const mapped_type &obj) noexcept {
    iterator it = find(key);

    if (it != end()) {
      return {it, false};
    } else {
      return tree_.insert({key, obj});
    }
  }

  std::pair<iterator, bool> insert_or_assign(const key_type &key,
                                             const mapped_type &obj) noexcept {
    iterator it = find(key);

    if (it != end()) {
      (*it).second = obj;
      return {it, false};
    }

    return tree_.insert({key, obj});
  }

  void erase(iterator pos) noexcept {
    iterator it = find((*pos).first);

    if (it != end()) {
      tree_.erase(*pos);
    }
  }

  void swap(map &other) noexcept { tree_.swap(other.tree_); }

  void merge(map &other) noexcept {
    for (const auto &pair : other) {
      tree_.insert(pair);
    }

    other.clear();
  }

  // Lookup
  bool contains(const key_type &key) const noexcept {
    iterator it = find(key);

    if (it != end()) {
      return true;
    } else {
      return false;
    }
  }

 private:
  RedBlackTree<value_type> tree_;

  iterator find(const key_type &key) const noexcept {
    iterator it = begin();

    while (it != end()) {
      if ((*it).first == key) {
        return it;
      }
      ++it;
    }

    return end();
  }
};
}  // namespace s21

#endif  // S21_MAP_H