// Copyright 2021 ak-kuznetsov <a.kuznetsov2701@mail.ru>

#ifndef INCLUDE_STACK_1_HPP_
#define INCLUDE_STACK_1_HPP_
#include <iostream>
template <typename T>
struct Node {
  T value;
  Node* next{nullptr};
};

template <typename T>
class Stack_1 {
 private:
  Node<T>* top{nullptr};

 public:
  Stack_1() = default;
  Stack_1(const Stack_1& stack) = delete;
  Stack_1(Stack_1&& stack) {
    this->top = stack.top;
    stack.top = nullptr;
  }
  auto operator=(const Stack_1& stack) = delete;
  auto operator=(Stack_1&& stack) -> Stack_1& {
    this->top = stack.top;
    stack.top = nullptr;
  }
  void push(T&& value) {
    Node<T>* new_node;
    new_node = top;
    top = new Node<T>;
    top->next = new_node;
    top->value = value;
  }
  void push(const T& value) {
    Node<T>* new_node;
    new_node = top;
    top = new Node<T>;
    top->next = new_node;
    top->value = std::move(value);
  }
  void pop() {
    if (top) {
      Node<T>* top_ = top->next;
      delete top;
      top = top_;
    } else {
      throw std::runtime_error("Empty stack pop");
    }
  }
  const T& head() {
    if (top)
      return top->value;
    else {
      throw std::runtime_error("Empty stack head");
    }
  }
  ~Stack_1() {
    while (top) {
      Node<T>* tmp = top->next;
      delete (top);
      top = tmp;
    }
  };
};
#endif  // INCLUDE_STACK_1_HPP_
