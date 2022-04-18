//
// Created by Ricardo Leite Jr on 7/21/20.
//

#ifndef STATION_H
#define STATION_H

#include "Vector.h"
#include "Stack.h"
#include "Queue.h"
#include "Deque.h"
#include <iterator>

template<typename T>
class Station : public Deque<T> {
private:
    Vector<T> train_;
    Stack<T> stack_;
    Queue<T> queue_;
    T turnTableCar_ = "-1";
    bool empty;

public:

    Station() {};

    ~Station() {};

/************************************
 * Vector train functions
 ***********************************/
    string addCar(const T &car);

    string removeCar();

    string topStation() {
        stringstream out;
        out << " " << turnTableCar_ << endl;
        return out.str();
    }

    string sizeVector() {
        stringstream out;
        out << " " << train_.size() << endl;
        return out.str();
    }

    string printTrainVector();

/************************************
 * Queue roundhouse functions
 ***********************************/

    string addToQueue();

    string removeFromQueue();

    string topQueue();

    string sizeQueue() {
        stringstream out;
        out << " " << queue_.size() << endl;
        return out.str();
    }

    string printQueue();

/************************************
 * Stack roundhouse functions
 ***********************************/

    string addToStack();

    string removeFromStack();

    string topStack();

    string stackSize() {
        stringstream out;
        out << " " << stack_.size() << endl;
        return out.str();
    }

    string printStack();

/*****************
 * Find <data>
******************/

    string find(T &value);

    string toString(const T &value) {
        return string(value);
    }


};


template<class T>
string Station<T>::addCar(const T &car) {
    stringstream out;

    string num = car;

    num.erase(0, num.find_first_not_of('0'));

    if (turnTableCar_ == "-1") {
        turnTableCar_ = num;
        out << " OK" << endl;
    } else {
        out << " Turntable occupied!" << endl;
    }
    return out.str();
}

template<class T>
string Station<T>::removeCar() {
    stringstream out;
    if (turnTableCar_ != "-1") {
        train_.push_back(turnTableCar_);
        turnTableCar_ = "-1";
        out << " OK" << endl;
    } else {
        out << " Turntable empty!" << endl;
    }
    return out.str();
}

template<class T>
string Station<T>::printTrainVector() {
    stringstream out;

    for (size_t i = 0; i < train_.size(); i++) {
        out << train_.at(i) << " ";
    }

    return out.str();
}

template<class T>
string Station<T>::addToQueue() {
    stringstream out;
    if (turnTableCar_ != "-1") {
        queue_.push(turnTableCar_);
        turnTableCar_ = "-1";
        out << " OK" << endl;
    } else {
        out << " Turntable empty!" << endl;
    }
    return out.str();
}

template<class T>
string Station<T>::removeFromQueue() {
    stringstream out;
    if (queue_.size() == 0) {
        out << " Queue empty!" << endl;
    } else if (turnTableCar_ != "-1") {
        out << " Turntable occupied!" << endl;
    } else {
        turnTableCar_ = queue_.top();
        queue_.pop();
        out << " OK" << endl;
    }

    return out.str();
}

template<class T>
string Station<T>::topQueue() {
    stringstream out;
    if (queue_.size() == 0) {
        out << " Queue empty!" << endl;
    } else {
        out << " " << queue_.top() << endl;
    }

    return out.str();
}

template<class T>
string Station<T>::printQueue() {

    stringstream out;

    for (size_t i = 0; i < queue_.size(); i++) {
        out << " " << queue_.at(i);
    }

    out << endl;

//    out << " " << queue_.top() << endl;

    return out.str();

}

template<class T>
string Station<T>::addToStack() {
    stringstream out;
    if (turnTableCar_ != "-1") {
        stack_.push(turnTableCar_);
        turnTableCar_ = "-1";
        out << " OK" << endl;
    } else {
        out << " Turntable empty!" << endl;
    }
    return out.str();
}

template<class T>
string Station<T>::removeFromStack() {
    stringstream out;
    if (stack_.size() == 0) {
        out << " Stack empty!" << endl;
    } else if (turnTableCar_ != "-1") {
        out << " Turntable occupied!" << endl;
    } else {
        turnTableCar_ = stack_.top();
        stack_.pop();
        out << " OK" << endl;
    }

    return out.str();
}

template<class T>
string Station<T>::topStack() {
    stringstream out;
    if (stack_.size() == 0) {
        out << " Stack empty!" << endl;
    } else {
        out << " " << stack_.top() << endl;
    }

    return out.str();
}

template<class T>
string Station<T>::printStack() {

    stringstream out;
    for (size_t i = 0; i < stack_.size(); i++) {
        out << " " << stack_.at(i);
    }
    out << endl;
    return out.str();

}

template<class T>
string Station<T>::find(T &value) {
    stringstream out;
    
    for (size_t i = 0; i < train_.size(); i++) {
        if (train_.at(i) == value) {
            out << " Train[" << i << "]" << endl;
            return out.str();
        }
    }
    for (size_t i = 0; i < queue_.size(); i++) {
        if (queue_.at(i) == value) {
            out << " Queue[" << i << "]" << endl;
            return out.str();
        }
    }
    for (size_t i = 0; i < stack_.size(); i++) {
        if (stack_.at(i) == value) {
            out << " Stack[" << i << "]" << endl;
            return out.str();
        }
    }

    out << " Not Found!" << endl;

    return out.str();
}

#endif //STATION_H
