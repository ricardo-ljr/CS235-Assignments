

#ifndef BTNODE_H
#define BTNODE_H

#include<iostream>
#include<sstream>

template<typename T>
struct Node {

    T data;
    Node<T> *left;
    Node<T> *right;

    Node(const T &the_data,
         Node<T> *left_val = NULL,
         Node<T> *right_val = NULL) : data(the_data), left(left_val), right(right_val) {};

    virtual ~Node() {};

    virtual std::string toString() const {
        std::ostringstream os;
        os << data;
        return os.str();
    }
};

template<typename T>
std::ostream &operator<<(std::ostream &out, const Node<T> &node) {
    return out << node.toString();
}

#endif //BTNODE_H
