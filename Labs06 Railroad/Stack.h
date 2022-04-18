//
// Created by Ricardo Leite Jr on 7/21/20.
//

#ifndef STACK_H
#define STACK_H

#include "Deque.h"

template<typename T>
class Stack {
private:
    Deque<T> stack_;

public:
    Stack() {};
    ~Stack() {};

    void push(T data) {
        stack_.push_back(data);
    }

    void pop(void) {
        stack_.pop_back();
    }

    T& top() {
        return stack_.back();
    }

    size_t size() const{
        return stack_.size();
    }

    T& at(size_t index) {
        return stack_.at(index);
    }

    string toString() const {
        stack_.toString();
    }
};

#endif //STACK_H
