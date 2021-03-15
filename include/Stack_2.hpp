// Copyright 2021 ak-kuznetsov <a.kuznetsov2701@mail.ru>

#ifndef INCLUDE_STACK_2_HPP_
#define INCLUDE_STACK_2_HPP_
#include <iostream>
template <typename T>
class Stack_2 {
 private:
  Node<T>* top = nullptr;

 public:
  Stack_2() = default;
  Stack_2(const Stack_2& stack) = delete;
  Stack_2(Stack_2&& stack) {
    this->top = stack.top;
    stack.top = nullptr;
  }
  auto operator=(const Stack_2& stack) = delete;
  auto operator=(Stack_2&& stack) -> Stack_2& {
    this->top = stack.top;
    stack.top = nullptr;
  }
  ~Stack_2() {
    while (top) {
      Node<T>* tmp = top->next;
      delete (top);
      top = tmp;
    }
  }
  template <typename... Args>
  void push_emplace(Args&&... value) {
    top = new Node<T>{{std::forward<Args>(value)...}, top};
  }
  void push(T&& value) {
    top = new Node<T>{std::forward<T>(value), top};
  }
  const T& head() const {
    if (top)
      return top->value;
    else {
      throw std::runtime_error("Empty stack head");
    }
  }
  T pop() {
    if (top) {
      auto* tmp = top;
      T data = std::move(top->value);
      top = top->next;
      delete tmp;
      return data;
    } else {
      throw std::runtime_error("Empty stack pop");
    }
  }
};
#endif  // INCLUDE_STACK_2_HPP_
