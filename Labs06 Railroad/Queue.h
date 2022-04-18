//
// Created by Ricardo Leite Jr on 7/21/20.
//

#ifndef QUEUE_H
#define QUEUE_H

#include "Deque.h"

template<typename T>
class Queue {
private:
    Deque<T> queue_;

public:
    Queue() {};
    ~Queue() {};

    void push(T data) {
        queue_.push_back(data);
    }

    void pop(void) {
        queue_.pop_front();
    }

    T& top() {
        return queue_.front();
    }

    size_t size() const {
        return queue_.size();
    }

    T& at(size_t index) {
        return queue_.at(index);
    }

    string toString() const {
        queue_.toString();
    }
};

#endif //QUEUE_H
