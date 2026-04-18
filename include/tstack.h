// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
 private:
  T data[size];  // NOLINT
  int topIndex;

 public:
  TStack() {
    topIndex = -1;
  }

  void push(T x) {
    if (topIndex < size - 1) {
      topIndex++;
      data[topIndex] = x;
    }
  }

  void pop() {
    if (topIndex >= 0) {
      topIndex--;
    }
  }

  T top() {
    return data[topIndex];
  }

  bool isEmpty() {
    return topIndex == -1;
  }
};

#endif  // INCLUDE_TSTACK_H_
