#pragma once
#include <cstddef>
#include <exception>
#include <initializer_list>
#include <memory>
#include <stdexcept>
namespace X {
template <typename T> class List {
private:
  struct Node {
    T data_;
    Node *prev;
    Node *next;
    Node(const T &d = T{}, Node *p = nullptr, Node *n = nullptr)
        : data_{d}, prev{p}, next{n} {}
    Node(T &&d, Node *p = nullptr, Node *n = nullptr)
        : data_{std::move(d)}, prev{p}, next{n} {}
  };

public:
  class const_iterator {
  protected:
    const List<T> *list_;
    Node *current_;

    T &retrieve() const {
      raiseIfInvalid();
      return current_->data_;
    }

    const_iterator(const List<T> &l_p, Node *n) : list_{&l_p}, current_{n} {}

    void raiseIfInvalid() const {
      if (list_ == nullptr || current_ == nullptr || current_ == list_->head_)
        throw std::out_of_range{"Invalid iterator"};
    }

    friend class List<T>;

  public:
    const_iterator() : current_{nullptr} {}

    const T &operator*() const { return this->retrieve(); }

    const_iterator &operator++() {
      current_ = current_->next;
      return *this;
    }

    // postfix operator
    const_iterator operator++(int) {
      const_iterator old = *this;
      ++(*this);
      return old;
    }

    const_iterator &operator--() {
      current_ = current_->prev;
      return *this;
    }

    // postfix operator
    const_iterator operator--(int) {
      const_iterator old = *this;
      --(*this);
      return old;
    }


    bool operator==(const const_iterator &rhs) const {
      return current_ == rhs.current_;
    }

    bool operator!=(const const_iterator &rhs) const { return !(*this == rhs); }
  };

  class iterator : public const_iterator {
  protected:
    iterator(const List<T> &l_p, Node *n) : const_iterator{l_p, n} {}
    friend class List<T>;

  public:
    iterator() : const_iterator() {}
    T &operator*() { return const_iterator::retrieve(); }
    const T &operator*() const { return const_iterator::operator*(); }

    iterator &operator++() {
      this->current_ = this->current_->next;
      return *this;
    }
    // postfix
    iterator operator++(int) {
      iterator old_val = *this;
      ++(*this);
      return old_val;
    }

    iterator &operator--() {
      this->current_ = this->current_->prev;
      return *this;
    }
    // postfix
    iterator operator--(int) {
      iterator old_val = *this;
      --(*this);
      return old_val;
    }

  };

private:
  size_t size_;
  // sentinel nodes head_ and tail_
  Node *head_;
  Node *tail_;

private:
  void init_empty() {
    size_ = 0;
    head_ = new Node;
    tail_ = new Node;
    head_->next = tail_;
    head_->prev = nullptr;

    tail_->prev = head_;
    tail_->next = nullptr;
  }

public:
  List() { init_empty(); }

  List(std::initializer_list<T> init) { 
    init_empty();
    for (const auto& e: init){
      push_back(e);
    } 
  }

  ~List() {
    clear();
    delete head_;
    delete tail_;
  }

  List(const List &rhs) {
    init_empty();
    for (const auto &e : rhs) {
      push_back(e);
    }
  }

  List &operator=(const List &rhs) {
    List tmp{rhs};
    std::swap(*this, tmp);
    return *this;
  }

  List(List &&rhs) : size_{rhs.size_}, head_{rhs.head_}, tail_{rhs.tail_} {
    rhs.size_ = 0;
    rhs.head_ = nullptr;
    rhs.tail_ = nullptr;
  }

  List &operator=(List &&rhs) {
    std::swap(size_, rhs.size_);
    std::swap(head_, rhs.head_);
    std::swap(tail_, rhs.tail_);
    return *this;
  }

  size_t size() const { return size_; }
  bool is_empty() const { return size_ == 0; }

  iterator begin() { return iterator{*this, head_->next}; }
  const_iterator begin() const { return const_iterator{*this, head_->next}; }
  iterator end() { return iterator{*this, tail_}; }
  const_iterator end() const { return const_iterator{*this, tail_}; }

  T &front() { return *begin(); }
  const T &front() const { return *begin(); }

  T &back() { return *(--end()); }
  const T &back() const { return *(--end()); }

  void push_front(const T &t) { insert(begin(), t); }
  void push_front(T &&t) { insert(begin(), std::move(t)); }

  void push_back(const T &t) { insert(end(), t); }
  void push_back(T &&t) { insert(end(), std::move(t)); }

  void pop_front() { erase(begin()); }
  void pop_back() { erase(--end()); }

  void clear() {
    while (!is_empty()) {
      pop_front();
    }
  }

  // insertion before the iterator position
  // return an iterator pointing to the new value
  iterator insert(iterator it, const T &t) {
    Node *curr_node = it.current_;
    Node *new_node = new Node{t, curr_node->prev, curr_node};
    curr_node->prev->next = new_node;
    curr_node->prev = new_node;
    size_ += 1;
    return iterator{*this, new_node};
  }

  // insertion before the iterator position
  // return an iterator pointing to the new value
  iterator insert(iterator it, T &&t) {
    Node *curr_node = it.current_;
    Node *new_node = new Node{std::move(t), curr_node->prev, curr_node};
    curr_node->prev->next = new_node;
    curr_node->prev = new_node;
    size_ += 1;
    return iterator{*this, new_node};
  }

  // erase the element pointed by iterator
  // return an iterator pointing to the next node after the deleted one
  iterator erase(iterator it) {
    Node *curr_node = it.current_;
    iterator retval{*this, curr_node->next};
    curr_node->prev->next = curr_node->next;
    curr_node->next->prev = curr_node->prev;
    delete curr_node;
    size_ -= 1;

    return retval;
  }

  iterator erase(iterator from_it, iterator to_it) {
    for (iterator i = from_it; i != to_it;) {
      i = erase(i);
    }
    return to_it;
  }
};

} // namespace X