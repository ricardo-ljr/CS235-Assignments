//
// Created by Ricardo Leite Jr on 7/21/20.
//

#ifndef DEQUE_H
#define DEQUE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

#include "DequeInterface.h"

template<typename T>
class Deque : public DequeInterface<T> {
private:
    struct Car {
        unsigned int id;

        Car() : id(0) {}

        ~Car() {}

        bool operator==(const Car car) { return this->id == car.id; }

        bool operator!=(const Car car) { return this->id != car.id; }

        /** Return the Car as a string */
        virtual string toString() const {
            stringstream out;
            out << id;
            return out.str();
        } // end toString()

        /** Make insertion operator friend for a Car */
        friend ostream &operator<<(ostream &os, const Car &c) {
            os << c.toString();
            return os;
        } // end operator<<
    };

    size_t capacity;
    size_t num_items;
    size_t front_index;
    size_t rear_index;
    T *the_data;

public:
//    Default constructor
    Deque(void) :
            capacity(DEFAULT_CAPACITY),
            num_items(0),
            front_index(0),
            rear_index(DEFAULT_CAPACITY - 1),
            the_data(new T[DEFAULT_CAPACITY]) {}

    ~Deque() {
        if (capacity > 0) delete[] the_data;
    };

    void reallocate();

    /** Insert item at front of deque */
    virtual void push_front(const T &value);

    /** Insert item at rear of deque */
    virtual void push_back(const T &value);

    /** Remove the front item of the deque */
    virtual void pop_front(void);

    /** Remove the rear item of the deque */
    virtual void pop_back(void);

    /** Return the front item of the deque (Do not remove) */
    virtual T &front(void);

    /** Return the rear item of the deque (Do not remove) */
    virtual T &back(void);

    /** Return the number of items in the deque */
    virtual size_t size(void) const { return num_items; }

    /** Return true if deque is empty */
    virtual bool empty(void) const { return num_items == 0; }

    /** Return item in deque at index (0 based) */
    virtual T &at(size_t index) { return the_data[(index + front_index) % capacity]; }

    /** Return the deque items */
    virtual std::string toString(void) const {
        for (int i = 0; i < capacity; i++) {
            if (i == front_index) {
                cout << "[front]" << the_data[i] << endl;
            } else if (i == rear_index) {
                cout << "[rear]" << the_data[i] << endl;
            } else {
                cout << i << the_data[i] << endl;
            }

            cout << "Number of Trains: " << num_items << endl;
            cout << "Index 0: " << the_data[0] << endl;
            cout << "Index 1: " << the_data[1] << endl;

        }
        return "Done";
    };


};

/**********************************************
 * resize: Dynamically resize data array
 **********************************************/

template<class T>
void Deque<T>::reallocate() {
    size_t newCapacity = 2 * capacity;
    T *newData = new T[newCapacity];

    size_t j = front_index;

    for (size_t i = 0; i < num_items; i++) {
        newData[i] = the_data[j];
        j = (j + 1) % capacity;
    }

    front_index = 0;
    rear_index = num_items - 1;
    capacity = newCapacity;
    std::swap(the_data, newData);

    delete[] newData;
}

/**********************************************
 * push_front: Insert item at front of deque
 **********************************************/

template<class T>
void Deque<T>::push_front(const T &value) {

    if (num_items == capacity) {
        reallocate();
    }

    if (num_items > 0) {
        front_index = (front_index - 1 < 0) ? capacity - 1 : front_index - 1;
    }

// Insert new item to front
    the_data[front_index] = value;
    num_items++;
}

/**********************************************
 * push_back: Insert item at rear of deque
 **********************************************/

template<class T>
void Deque<T>::push_back(const T &value) {

    if (num_items == capacity) {
        reallocate();
    }

    num_items++;

    rear_index = (rear_index + 1) % capacity;
    the_data[rear_index] = value;
}

/**********************************************
 * pop_front: Remove the front item of the deque
 **********************************************/

template<class T>
void Deque<T>::pop_front() {

    front_index = (front_index + 1) % capacity;
    num_items--;

//    front_index++;
//    if (front_index == capacity) {
//        delete[] the_data.front();
//        the_data.pop_front();
//        front_index = 0;
//    }
//    num_items--;
}

/**********************************************
 * pop_back: Remove the rear item of the deque
 **********************************************/

template<class T>
void Deque<T>::pop_back() {

    rear_index = (rear_index - 1 < 0) ? capacity - 1 : rear_index - 1;
    num_items--;
}

/***********************************************************
 * front: Return the front item of the deque (Do not remove)
 ***********************************************************/

template<class T>
T &Deque<T>::front() {

    return the_data[front_index];
}

/***********************************************************
 * back: Return the rear item of the deque (Do not remove)
 ***********************************************************/

template<class T>
T &Deque<T>::back() {

    return the_data[rear_index];
}


#endif //DEQUE_H
