#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "LinkedListInterface.h"

using namespace std;


template<typename T>
class LinkedList : public LinkedListInterface<T> {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& d) : data(d), next(NULL) {}
        Node(const T& d, Node* n) : data(d), next(n) {}
    };
    Node* head;

public:
    LinkedList() {this->head = NULL;}
    ~LinkedList(void) {clear(); }

    /* Function to add to the head of list */

    virtual void push_front(const T& value) {
        head = new Node(value, head);
    }

    /* Function to print list */

    virtual std::string toString(void) const {
        std::stringstream  out;
        Node* ptr = head;
        if (ptr == NULL) {
            out << " Empty!";
        }

        while (ptr != NULL) {
            out << " " << ptr->data;
            ptr = ptr->next;
        }
        return out.str();
    }

    /* Function to clear list */

    virtual void clear(void) {

        Node* ptr = head;
        Node* next;

        if (ptr == NULL) {
            return;
        }
        while (ptr != NULL) {
            next = ptr->next;
            delete ptr;
            ptr = next;
        }

        head = NULL;
    }

    virtual size_t size(void) const {
        int listSize = 0;
        Node* ptr = head;
        if (head == NULL) {
            return 0;
        }
        while (ptr != NULL) {
            listSize++;
            ptr = ptr->next;
        }
        return listSize;
    }

    virtual void pop_front(void) {
        std::stringstream out;
        Node* ptr = head;
        try {
            if (ptr == NULL) {
                throw std::string("Delete Empty!\n");
            } else {
                head = head->next;
                delete ptr;
            }
        } catch (...) {
            out << "Delete Empty!" << std::endl;
        }
    }

    friend std::ostream& operator << (std::ostream& os, LinkedList<T>& linkedList) {
        for (Iterator iter = linkedList.begin(); iter != linkedList.end(); ++iter)
        {
            os << *iter << " ";
        }
        return os;
    }

    class Iterator {
        friend class LinkedList;
    private:
        Node* iNode;

    public:
        Iterator(Node* head) : iNode(head) { }
        ~Iterator() {}

//        Overload the comparison operator
        bool operator!=(const Iterator& itr) const {
            return iNode != itr.iNode;
        }

//        Overload for the postincrement operator ++
        Iterator& operator++() {
             iNode = iNode->next;
            return *this;
        }
//        Overload for the dereference operator
        T& operator*() const {
            return iNode->data;
        }
    };

    /** Return iterator pointing to the first value in linked list */
    Iterator begin(void) {
        return LinkedList<T>::Iterator(head);
    }

    /** Return iterator pointing to something not in linked list */
    Iterator end(void) {
        return LinkedList<T>::Iterator(NULL);
    }

    /** Return iterator pointing found value in linked list */
    Iterator find(Iterator first, Iterator last, const T& value) {
        while (first != last) {
            if (*first == value) return first;
            ++first;
        }
       return last;
    }

    /** Return iterator pointing to inserted value in linked list */
    Iterator insert(Iterator position, const T& value) {
        Iterator temp = begin();
        while (temp.iNode != position.iNode) {
            ++temp;
        }
        Node* ptr = new Node(value, temp.iNode);
        ptr->next = temp.iNode->next;
        temp.iNode->next = ptr;
        ptr->data = temp.iNode->data;
        temp.iNode->data = value;

        return position;
    }

    /** Return iterator pointing to inserted value in linked list */
    Iterator insert_after(Iterator position, const T& value) {
        Iterator temp = begin();
        while (temp.iNode != position.iNode) {
            ++temp;
        }
        Node* ptr = new Node(value, temp.iNode->next);
        ptr->next = temp.iNode->next;
        temp.iNode->next = ptr;


        return position;
    }

    /** Return iterator pointing to next item after deleted node linked list */
    Iterator erase(Iterator position) {
        Iterator temp = begin();
        if (position.iNode == head) pop_front();
        else if (position.iNode == NULL) return position;
        else if (position.iNode != head) {
            while (temp.iNode->next != position.iNode) {
                ++temp;
            }
            temp.iNode->next = position.iNode->next;

            delete position.iNode;
        }

        return position;

    }

    /** Replace first found old_value(s) with new_value */
    void replace(Iterator first, Iterator last, const T& old_value, const T& new_value)
    {
        while (first != last) {
            if (*first == old_value) *first = new_value;
            ++first;
        }
    }
};

#endif //LINKEDLIST_H