//
// Created by Ricardo Leite Jr on 7/21/20.
//

#ifndef VECTOR_H
#define VECTOR_H

#include "Deque.h"

template<typename T>
class Vector{
private:
    Deque<T> vector_;

public:

    Vector() {};
    ~Vector() {};
    void push_back(T data) {
        vector_.push_back(data);
    }

    void pop_back(void) {
        vector_.pop_back();
    }

    T& back() {
        return vector_.back();
    }

    size_t size() const {
        return vector_.size();
    }

    T &at(size_t index) {
        return vector_.at(index);
    }

    string toString() const {
        vector_.toString();
    }
};

#endif //VECTOR_H
