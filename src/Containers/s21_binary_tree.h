#ifndef S21_BINARY_TREE_H
#define S21_BINARY_TREE_H

#include <limits>
#include <stdexcept>
#include <utility>

namespace s21 {
template <typename T>
class RedBlackTree {
 public:
  using key_value = T;

 private:
  enum Color { RED, BLACK };

  struct Node {
    key_value data;
    Node* parent;
    Node* left;
    Node* right;
    Color color;
  };

  class iterator {
   public:
    explicit iterator(Node* node) noexcept : current_(node) {}

    iterator& operator++() noexcept {
      if (current_->right) {
        current_ = Minimum(current_->right);
      } else {
        Node* parent = current_->parent;
        while (parent && current_ == parent->right) {
          current_ = parent;
          parent = parent->parent;
        }
        current_ = parent;
      }

      return *this;
    }

    iterator& operator++(int) noexcept {
      if (current_->right) {
        current_ = Minimum(current_->right);
      } else {
        Node* parent = current_->parent;
        while (parent && current_ == parent->right) {
          current_ = parent;
          parent = parent->parent;
        }
        current_ = parent;
      }

      return *this;
    }

    key_value& operator*() const noexcept { return current_->data; }

    bool operator==(const iterator& other) const noexcept {
      return current_ == other.current_;
    }

    bool operator!=(const iterator& other) const noexcept {
      return current_ != other.current_;
    }

   private:
    Node* current_;
  };

 public:
  using iterator = iterator;
  using const_iterator = const iterator;

  RedBlackTree() noexcept : root_(nullptr) {}

  ~RedBlackTree() noexcept { DestroyTree(root_); }

  iterator begin() const noexcept { return iterator(Minimum(root_)); }

  iterator end() const noexcept { return iterator(nullptr); }

  bool empty() const noexcept { return root_ == nullptr; }

  size_t size() const noexcept { return size(root_); }

  size_t max_size() const noexcept {
    return std::numeric_limits<size_t>::max() / sizeof(Node);
  }

  void clear() noexcept {
    clear(root_);
    root_ = nullptr;
  }

  std::pair<iterator, bool> insert(key_value value) noexcept {
    if (!root_) {
      root_ = new Node{value, nullptr, nullptr, nullptr, BLACK};
      return {iterator(root_), true};
    }

    Node* new_node = new Node{value, nullptr, nullptr, nullptr, RED};
    Node* parent = nullptr;
    Node* current = root_;

    while (current) {
      parent = current;
      if (value < current->data) {
        current = current->left;
      } else if (current->data < value) {
        current = current->right;
      } else {
        delete new_node;
        return {iterator(current), false};
      }
    }

    new_node->parent = parent;
    if (value < parent->data) {
      parent->left = new_node;
    } else {
      parent->right = new_node;
    }

    InsertFixup(new_node);
    return {iterator(new_node), true};
  }

  void erase(key_value value) noexcept {
    Node* node = FindNode(value);

    if (!node) {
      return;
    }

    Node* to_delete = node;
    Color to_delete_original_color = to_delete->color;
    Node* replacement = nullptr;

    if (!node->left) {
      replacement = node->right;
      Transplant(node, node->right);
    } else if (!node->right) {
      replacement = node->left;
      Transplant(node, node->left);
    } else {
      to_delete = Minimum(node->right);
      to_delete_original_color = to_delete->color;
      replacement = to_delete->right;

      if (to_delete->parent == node) {
        if (replacement) {
          replacement->parent = to_delete;
        }
      } else {
        Transplant(to_delete, to_delete->right);
        to_delete->right = node->right;
        if (node->right) {
          node->right->parent = to_delete;
        }
      }

      Transplant(node, to_delete);
      to_delete->left = node->left;
      to_delete->left->parent = to_delete;
      to_delete->color = node->color;
    }

    delete node;

    if (to_delete_original_color == BLACK) {
      DeleteFixup(replacement, to_delete->parent);
    }
  }

  void swap(RedBlackTree& other) noexcept { std::swap(root_, other.root_); }

  bool contains(key_value value) const noexcept {
    Node* current = root_;

    while (current) {
      if (value == current->data) {
        return true;
      } else if (value < current->data) {
        current = current->left;
      } else {
        current = current->right;
      }
    }

    return false;
  }

 private:
  Node* root_;

  Node* FindNode(const key_value& value) const {
    Node* current = root_;

    while (current) {
      if (value == current->data) {
        return current;
      } else if (value < current->data) {
        current = current->left;
      } else {
        current = current->right;
      }
    }

    return nullptr;
  }

  void DestroyTree(Node* node) noexcept {
    if (node) {
      DestroyTree(node->left);
      DestroyTree(node->right);

      delete node;
    }
  }

  size_t size(Node* node) const noexcept {
    if (node == nullptr) {
      return 0;
    }

    size_t left_size = size(node->left);
    size_t right_size = size(node->right);

    return left_size + right_size + 1;
  }

  void clear(Node* node) noexcept {
    if (node == nullptr) {
      return;
    }

    clear(node->left);
    clear(node->right);

    delete node;
  }

  void RotateLeft(Node* node) noexcept {
    if (!node || !node->right) {
      return;
    }

    Node* right_child = node->right;
    node->right = right_child->left;

    if (right_child->left) {
      right_child->left->parent = node;
    }

    right_child->parent = node->parent;

    if (!node->parent) {
      root_ = right_child;
    } else if (node == node->parent->left) {
      node->parent->left = right_child;
    } else {
      node->parent->right = right_child;
    }

    right_child->left = node;
    node->parent = right_child;
  }

  void RotateRight(Node* node) noexcept {
    if (!node || !node->left) {
      return;
    }

    Node* left_child = node->left;
    node->left = left_child->right;

    if (left_child->right) {
      left_child->right->parent = node;
    }

    left_child->parent = node->parent;

    if (!node->parent) {
      root_ = left_child;
    } else if (node == node->parent->left) {
      node->parent->left = left_child;
    } else {
      node->parent->right = left_child;
    }

    left_child->right = node;
    node->parent = left_child;
  }

  void InsertFixup(Node* node) noexcept {
    while (node != root_ && node->parent && node->parent->color == RED) {
      if (node->parent == node->parent->parent->left) {
        Node* uncle = node->parent->parent->right;

        if (uncle && uncle->color == RED) {
          node->parent->color = BLACK;
          uncle->color = BLACK;
          node->parent->parent->color = RED;
          node = node->parent->parent;
        } else {
          if (node == node->parent->right) {
            node = node->parent;
            RotateLeft(node);
          }

          node->parent->color = BLACK;
          node->parent->parent->color = RED;
          RotateRight(node->parent->parent);
        }
      } else {
        Node* uncle = node->parent->parent->left;

        if (uncle && uncle->color == RED) {
          node->parent->color = BLACK;
          uncle->color = BLACK;
          node->parent->parent->color = RED;
          node = node->parent->parent;
        } else {
          if (node == node->parent->left) {
            node = node->parent;
            RotateRight(node);
          }

          node->parent->color = BLACK;
          node->parent->parent->color = RED;
          RotateLeft(node->parent->parent);
        }
      }
    }

    root_->color = BLACK;
  }

  void DeleteFixup(Node* node, Node* parent) noexcept {
    Node* sibling;

    while (node != root_ && (node == nullptr || node->color == BLACK)) {
      if (node == parent->left) {
        sibling = parent->right;

        if (sibling && sibling->color == RED) {
          sibling->color = BLACK;
          parent->color = RED;
          RotateLeft(parent);
          sibling = parent->right;
        }

        if ((!sibling->left || sibling->left->color == BLACK) &&
            (!sibling->right || sibling->right->color == BLACK)) {
          sibling->color = RED;
          node = parent;
        } else {
          if (!sibling->right || sibling->right->color == BLACK) {
            if (sibling->left) {
              sibling->left->color = BLACK;
            }
            sibling->color = RED;
            RotateRight(sibling);
            sibling = parent->right;
          }

          sibling->color = parent->color;
          parent->color = BLACK;
          if (sibling->right) {
            sibling->right->color = BLACK;
          }
          RotateLeft(parent);
          node = root_;
        }
      } else {
        sibling = parent->left;

        if (sibling && sibling->color == RED) {
          sibling->color = BLACK;
          parent->color = RED;
          RotateRight(parent);
          sibling = parent->left;
        }

        if ((!sibling->right || sibling->right->color == BLACK) &&
            (!sibling->left || sibling->left->color == BLACK)) {
          sibling->color = RED;
          node = parent;
        } else {
          if (!sibling->left || sibling->left->color == BLACK) {
            if (sibling->right) {
              sibling->right->color = BLACK;
            }
            sibling->color = RED;
            RotateLeft(sibling);
            sibling = parent->left;
          }

          sibling->color = parent->color;
          parent->color = BLACK;
          if (sibling->left) {
            sibling->left->color = BLACK;
          }
          RotateRight(parent);
          node = root_;
        }
      }

      if (node) {
        node->color = BLACK;
      }
    }
  }

  void Transplant(Node* u, Node* v) noexcept {
    if (!u->parent) {
      root_ = v;
    } else if (u == u->parent->left) {
      u->parent->left = v;
    } else {
      u->parent->right = v;
    }

    if (v) {
      v->parent = u->parent;
    }
  }

  static Node* Minimum(Node* node) noexcept {
    while (node && node->left) {
      node = node->left;
    }

    return node;
  }
};
}  // namespace s21

#endif  // S21_BINARY_TREE_H
