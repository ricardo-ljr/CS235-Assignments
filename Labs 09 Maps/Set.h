

#ifndef SET_H
#define SET_H

#include <string>
#include <sstream>
#include <list>
#include <algorithm>

using namespace std;

#include "SetInterface.h"

template<typename T>
class Set : public SetInterface<T> {
private:
    list<T> list_;
public:
    Set() {}

    Set(std::initializer_list<T> list) : list_(list) {
        list_.sort();
        list_.unique();
        list_.begin();
        list_.end();
    }

    size_t count(const T &item) {
        return (find(list_.begin(), list_.end(), item) != list_.end());
    }

    /** Inserts item into the set, if the container doesn't
        already contain an element with an equivalent value.
        @return: pair.first = pointer to item
                 pair.second = true if successfully inserted, else false. */
    //virtual Pair<T*, bool> insert(const T& item) = 0;
    virtual bool insert(const T &item) {

        if (find(list_.begin(), list_.end(), item) != list_.end()) {
            return false;
        } else {
            list_.push_back(item);
            list_.sort();
            return true;
        }
    }

    virtual size_t findIndex(const T &item) {
        for (auto i = list_.begin(); i != list_.end(); i++) {
            if (*i == item) return true;
        }
        return 0;
    }

    /** Removes all items from the set. */
    virtual void clear() {
        list_.clear();
    }

    /** @return: the number of elements contained by the Set. */
    virtual size_t size() const {}

    /** @return: string representation of items in Set. */
    virtual std::string toString() const {
        stringstream ss;
        string order;
        for (auto i = list_.begin(); i != list_.end(); i++) {
            ss << order << *i;
            order = ",";
        }
        return ss.str();

    }

    friend std::ostream &operator<<(std::ostream &out, const Set<T> set) {
        out << set.toString();
        return out;
    }
};


#endif //SET_H
