#ifndef S21_LIST_H
#define S21_LIST_H

#include <limits>
#include <stdexcept>
#include <utility>

namespace s21 {
template <typename T>
class list {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const value_type &;
  using size_type = size_t;

 private:
  struct ListNode {
    explicit ListNode(const value_type &value)
        : data(value), next(nullptr), prev(nullptr){};

    value_type data;
    ListNode *next;
    ListNode *prev;
  };

  class ListIterator {
   public:
    explicit ListIterator(ListNode *p = 0) : ptr_(p) {}

    reference operator*() const noexcept { return ptr_->data; }
    value_type *operator->() const noexcept { return &(ptr_->data); }

    bool operator!=(const ListIterator &rhs) const noexcept {
      return this->ptr_ != rhs.ptr_;
    }
    bool operator==(const ListIterator &rhs) const noexcept {
      return this->ptr_ == rhs.ptr_;
    }

    ListIterator operator++(int) noexcept {
      ptr_ = ptr_->next;
      return *this;
    }
    ListIterator &operator++() noexcept {
      ptr_ = ptr_->next;
      return *this;
    }

    ListIterator operator--(int) noexcept {
      ptr_ = ptr_->prev;
      return *this;
    }
    ListIterator &operator--() noexcept {
      ptr_ = ptr_->prev;
      return *this;
    }

    ListNode *GetPtr() const noexcept { return ptr_; }

   private:
    ListNode *ptr_ = nullptr;
  };

 public:
  using iterator = ListIterator;
  using const_iterator = const ListIterator;

  list() noexcept : head_(nullptr), tail_(nullptr), size_(0){};

  explicit list(size_type n) : head_(nullptr), tail_(nullptr), size_(0) {
    if (n >= max_size()) {
      throw std::out_of_range("Out of container's limit");
    }

    for (size_type i = 0; i < n; ++i) {
      push_back(value_type());
    }
  }

  list(const std::initializer_list<value_type> &items) noexcept
      : head_(nullptr), tail_(nullptr), size_(0) {
    for (const T &item : items) {
      this->push_back(item);
    }
  }

  list(const list &l) noexcept : head_(nullptr), tail_(nullptr), size_(0) {
    ListNode *current = l.head_;

    while (current != nullptr) {
      this->push_back(current->data);
      current = current->next;
    }
  }

  list(list &&l) noexcept : head_(nullptr), tail_(nullptr), size_(0) {
    this->swap(l);
  }

  ~list() noexcept {
    ListNode *current(this->head_);

    while (current) {
      ListNode *next(current->next);
      delete current;
      current = next;
    }
  }

  list &operator=(list &&l) noexcept {
    this->clear();
    this->swap(l);

    return *this;
  }

  // Element access
  const_reference front() const noexcept { return this->head_->data; }

  const_reference back() const noexcept { return this->tail_->data; }

  // Iterators
  iterator begin() const noexcept { return iterator(this->head_); }

  iterator end() const noexcept { return iterator(this->tail_); }

  // Capacity
  bool empty() const noexcept { return this->size_ == 0; }

  size_type size() const noexcept { return this->size_; }

  size_type max_size() const noexcept {
    return (std::numeric_limits<size_type>::max() / sizeof(ListNode)) / 2;
  }

  // Modifiers
  void clear() noexcept {
    while (!this->empty()) {
      this->pop_back();
    }
  }

  iterator insert(iterator pos, const_reference value) noexcept {
    auto *new_node = new ListNode(value);

    if (pos == this->begin()) {
      new_node->next = this->head_;
      new_node->prev = nullptr;
      if (this->head_) {
        this->head_->prev = new_node;
      }
      this->head_ = new_node;
    } else if (pos == this->end()) {
      new_node->next = nullptr;
      new_node->prev = this->tail_;
      if (this->tail_) {
        this->tail_->next = new_node;
      }
      this->tail_ = new_node;
    } else {
      auto *current_node = pos.GetPtr();
      new_node->next = current_node;
      new_node->prev = current_node->prev;
      current_node->prev->next = new_node;
      current_node->prev = new_node;
    }

    ++this->size_;
    return iterator(new_node);
  }

  void erase(iterator pos) {
    if (pos == this->end() || empty()) {
      throw std::invalid_argument("End or empty");
    }

    auto *current_node = pos.GetPtr();

    if (current_node == this->head_) {
      this->head_ = current_node->next;
      if (this->head_) {
        this->head_->prev = nullptr;
      }
    } else if (current_node == this->tail_) {
      this->tail_ = current_node->prev;
      if (this->tail_) {
        this->tail_->next = nullptr;
      }
    } else {
      current_node->prev->next = current_node->next;
      current_node->next->prev = current_node->prev;
    }

    delete current_node;
    --this->size_;
  }

  void push_back(const_reference value) noexcept {
    auto *node = new ListNode(value);

    node->prev = this->tail_;
    node->next = nullptr;

    if (this->tail_) {
      this->tail_->next = node;
    }

    this->tail_ = node;

    if (this->head_ == nullptr) {
      this->head_ = node;
    }

    ++this->size_;
  }

  void pop_back() noexcept {
    if (this->tail_) {
      auto *node = this->tail_;

      this->tail_ = this->tail_->prev;

      if (this->tail_) {
        this->tail_->next = nullptr;
      } else {
        this->head_ = nullptr;
      }

      delete node;
      --this->size_;
    }
  }

  void push_front(const_reference value) noexcept {
    auto *node = new ListNode(value);

    node->next = this->head_;
    node->prev = nullptr;

    if (this->head_) {
      this->head_->prev = node;
    }

    this->head_ = node;

    if (this->tail_ == nullptr) {
      this->tail_ = node;
    }

    ++this->size_;
  }

  void pop_front() noexcept {
    if (this->head_) {
      auto *node = this->head_;

      this->head_ = this->head_->next;

      if (this->head_) {
        this->head_->prev = nullptr;
      } else {
        this->tail_ = nullptr;
      }

      delete node;
      --this->size_;
    }
  }

  void swap(list &other) noexcept {
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
    std::swap(size_, other.size_);
  }

  // Operations
  void merge(list &other) noexcept {
    if (this == &other || other.empty()) {
      return;
    }

    if (empty()) {
      swap(other);
      return;
    }

    list merged_list;

    auto it1 = begin();
    auto it2 = other.begin();

    while (it1 != end() || it2 != other.end()) {
      if (*it1 <= *it2) {
        merged_list.push_back(*it1);
        ++it1;
      } else {
        merged_list.push_back(*it2);
        ++it2;
      }
    }

    if (*it1 < *it2) {
      merged_list.push_back(*it1);
      merged_list.push_back(*it2);
    } else {
      merged_list.push_back(*it2);
      merged_list.push_back(*it1);
    }

    other.clear();
    swap(merged_list);
  }

  void splice(const_iterator pos, list &other) noexcept {
    if (this == &other || other.empty()) {
      return;
    }

    if (empty()) {
      swap(other);
      return;
    }

    iterator first = other.begin();
    iterator last = other.end();

    while (first != last) {
      iterator next = first;
      ++next;
      insert(pos, *first);
      first = next;
    }

    insert(pos, *first);

    other.clear();
  }

  void reverse() noexcept {
    if (size_ <= 1) {
      return;
    }

    ListNode *current = head_;
    ListNode *temp;

    std::swap(head_, tail_);

    while (current != nullptr) {
      temp = current->prev;
      current->prev = current->next;
      current->next = temp;
      current = current->prev;
    }
  }

  void unique() noexcept {
    if (size_ <= 1) {
      return;
    }

    ListNode *current = head_;

    while (current != nullptr && current->next != nullptr) {
      if (current->data == current->next->data) {
        ListNode *duplicate = current->next;
        current->next = duplicate->next;

        if (duplicate->next != nullptr) {
          duplicate->next->prev = current;
        } else {
          tail_ = current;
        }

        --size_;
      } else {
        current = current->next;
      }
    }
  }

  void sort() noexcept {
    if (size_ <= 1) {
      return;
    }

    bool swapped;
    do {
      swapped = false;
      ListNode *current = head_;
      ListNode *next_node = current->next;

      while (next_node != nullptr) {
        if (current->data > next_node->data) {
          std::swap(current->data, next_node->data);
          swapped = true;
        }

        current = next_node;
        next_node = next_node->next;
      }
    } while (swapped);
  }

 private:
  ListNode *head_;
  ListNode *tail_;

  size_type size_;
};
}  // namespace s21

#endif  // S21_LIST_H