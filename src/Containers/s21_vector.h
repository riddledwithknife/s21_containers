#ifndef S21_VECTOR_H
#define S21_VECTOR_H

#include <initializer_list>
#include <limits>
#include <stdexcept>
#include <utility>

namespace s21 {
template <typename T>
class vector {
 public:
  using value_type = T;
  using reference = T &;
  using pointer = T *;
  using const_reference = const value_type &;
  using size_type = size_t;

 private:
  class VectorIterator {
   public:
    explicit VectorIterator(pointer ptr) : ptr_(ptr) {}

    reference operator*() const noexcept { return *ptr_; }
    value_type *operator->() const noexcept { return ptr_; }

    bool operator!=(const VectorIterator &rhs) const noexcept {
      return ptr_ != rhs.ptr_;
    }
    bool operator==(const VectorIterator &rhs) const noexcept {
      return ptr_ == rhs.ptr_;
    }

    bool operator<(const VectorIterator &rhs) const noexcept {
      return ptr_ < rhs.ptr_;
    }
    bool operator<=(const VectorIterator &rhs) const noexcept {
      return ptr_ <= rhs.ptr_;
    }
    bool operator>(const VectorIterator &rhs) const noexcept {
      return ptr_ > rhs.ptr_;
    }
    bool operator>=(const VectorIterator &rhs) const noexcept {
      return ptr_ >= rhs.ptr_;
    }

    VectorIterator operator++(int) noexcept {
      VectorIterator temp = *this;
      ++ptr_;
      return temp;
    }
    VectorIterator &operator++() noexcept {
      ++ptr_;
      return *this;
    }
    VectorIterator operator--(int) noexcept {
      VectorIterator temp = *this;
      --ptr_;
      return temp;
    }
    VectorIterator &operator--() noexcept {
      --ptr_;
      return *this;
    }

   private:
    pointer ptr_ = nullptr;
  };

 public:
  using iterator = VectorIterator;
  using const_iterator = const VectorIterator;

  vector() : data_(nullptr), size_(0), capacity_(0){};

  explicit vector(size_type n) : size_(n), capacity_(n) {
    data_ = new value_type[capacity_];

    for (size_type i = 0; i < size_; ++i) {
      new (&data_[i]) value_type();
    }
  };

  vector(std::initializer_list<value_type> const &items)
      : size_(items.size()), capacity_(items.size()) {
    data_ = new value_type[capacity_];

    size_type i = 0;
    for (const auto &item : items) {
      new (&data_[i++]) value_type(item);
    }
  }

  vector(const vector &v) : size_(v.size_), capacity_(v.size_) {
    data_ = new value_type[capacity_];

    for (size_type i = 0; i < size_; ++i) {
      new (&data_[i]) value_type(v.data_[i]);
    }
  }

  vector(vector &&v) noexcept
      : data_(v.data_), size_(v.size_), capacity_(v.capacity_) {
    v.data_ = nullptr;
    v.size_ = 0;
    v.capacity_ = 0;
  }

  ~vector() noexcept {
    if (this->data_) {
      delete[] this->data_;
    }

    this->data_ = nullptr;
    this->size_ = this->capacity_ = 0;
  }

  vector &operator=(vector &&v) noexcept {
    if (this != &v) {
      delete[] data_;

      data_ = v.data_;
      size_ = v.size_;
      capacity_ = v.capacity_;

      v.data_ = nullptr;
      v.size_ = v.capacity_ = 0;
    }

    return *this;
  }

  // Element access
  reference at(size_type pos) const {
    if (pos >= this->size_) {
      throw std::out_of_range("Index out of bounds");
    }

    return data_[pos];
  }

  reference operator[](size_type pos) const noexcept { return data_[pos]; }

  const_reference front() const noexcept { return data_[0]; }

  const_reference back() const noexcept { return data_[size_ - 1]; }

  pointer data() const noexcept { return data_; }

  // Iterators
  iterator begin() const noexcept { return iterator(data_); }

  iterator end() const noexcept { return iterator(data_ + size_); }

  // Capacity
  bool empty() const noexcept { return size_ == 0; }

  size_type size() const noexcept { return size_; }

  size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max() / sizeof(value_type) / 2;
  }

  void reserve(size_type size) noexcept {
    if (size <= capacity_) {
      return;
    }

    auto *new_data = new value_type[size];

    for (size_type i = 0; i < size_; ++i) {
      new_data[i] = std::move(data_[i]);
    }

    delete[] data_;

    data_ = new_data;
    capacity_ = size;
  }

  size_type capacity() const noexcept { return capacity_; }

  void shrink_to_fit() noexcept {
    if (size_ == capacity_) {
      return;
    }

    if (size_ == 0) {
      delete[] data_;
      data_ = nullptr;
      capacity_ = 0;
    } else {
      auto *new_data = new value_type[size_];

      for (size_type i = 0; i < size_; ++i) {
        new_data[i] = data_[i];
      }

      delete[] data_;

      data_ = new_data;
      capacity_ = size_;
    }
  }

  // Modifiers
  void clear() noexcept { size_ = 0; }

  void insert(iterator pos, const_reference value) noexcept {
    if (size_ >= capacity_) {
      size_type new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
      reserve(new_capacity);
    }

    size_type index = 0;
    iterator it = begin();
    while (it <= pos) {
      ++it;
      ++index;
    }

    for (size_type i = size_; i > index; --i) {
      data_[i] = std::move(data_[i - 1]);
    }

    data_[index] = value;

    ++size_;
  }

  void erase(iterator pos) {
    size_type index = 0;
    iterator it = begin();
    while (it != pos) {
      ++it;
      ++index;
    }

    if (index >= size_) {
      throw std::out_of_range("Index out of bounds");
    }

    for (size_type i = index; i < size_ - 1; ++i) {
      data_[i] = std::move(data_[i + 1]);
    }

    data_[size_ - 1].~value_type();

    --size_;
  }

  void push_back(const_reference value) noexcept {
    if (size_ >= capacity_) {
      size_type new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
      reserve(new_capacity);
    }

    data_[size_] = value;

    ++size_;
  }

  void pop_back() noexcept {
    if (size_ > 0) {
      data_[size_ - 1].~value_type();

      --size_;
    }
  }

  void swap(vector &other) noexcept {
    std::swap(data_, other.data_);

    std::swap(size_, other.size_);

    std::swap(capacity_, other.capacity_);
  }

 private:
  value_type *data_;
  size_type size_;
  size_type capacity_;
};
}  // namespace s21

#endif  // S21_VECTOR_H
