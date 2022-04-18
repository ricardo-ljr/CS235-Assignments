

#ifndef HASHMAP_H
#define HASHMAP_H

#include "HashMapInterface.h"
#include "Set.h"
#include "Pair.h"
//#include <utility>
#include <cmath>
#include <iostream>
#include <string>

using namespace std;

template<typename K, typename V>
class HashMap : public HashMapInterface<K, V> {
private:
    size_t max_size_;
    Pair<K, V> *myPairs;
    size_t numItems;

    size_t setHash(const K &key) {
        size_t hash = 0;
        for (size_t i = 0; i < key.size(); i++) {
            hash += key[i] * pow(HASH_CONSTANT, key.size() - (i + 1));
        }
        hash %= max_size_;
        return hash;
    }


public:

    HashMap() : myPairs(new Pair<K, V>[max_size_]), max_size_(DEFAULT_MAP_HASH_TABLE_SIZE) { numItems = 0; }

    ~HashMap() { clear(); }


    virtual V &operator[](const K &key) {
        size_t base = setHash(key);
        size_t index = base;
        size_t counter = 1;

        if ((numItems * 100 / max_size_) >= LOAD_THRESHOLD) {
            rehash();
        }

        while (true) {

            if (myPairs[index].first != K()) {
                if (myPairs[index].first == key) break;

                index = base + pow(counter++, 2);
                index %= max_size_;
            } else {
                myPairs[index].first = key;
                numItems++;
                break;
            }

        }


        return myPairs[index].second;
    }

    void rehash() {
        size_t oldCapacity = max_size_;
        Pair<K, V> *tempArray = myPairs;
        max_size_ = max_size_ * 2;
        myPairs = new Pair<K, V>[max_size_];
        numItems = 0;
        for (size_t i = 0; i < oldCapacity; i++) {
            if (tempArray[i].first != K()) {
                (*this)[tempArray[i].first] = tempArray[i].second;
            }
        }
        delete[] tempArray;

    }

    /** @return: the number of elements that match the key in the Map. */
    virtual size_t count(const K &key) {
        size_t counter = 0;

        for (size_t i = 0; i < max_size_; i++) {
            if (myPairs[i].first == key) counter++;
        }
        return counter;
    };

    /** Removes all items from the Map. */
    virtual void clear(void) {
        delete[] myPairs;
        myPairs = nullptr;
        numItems = 0;
    };

    /** @return: number of Key-Value pairs stored in the Map. */
    virtual size_t size(void) const {
        return numItems;
    };

    /** @return: maximum number of Key-Value pairs that the Map can hold. */
    virtual size_t max_size(void) const {
        return max_size_;
    };

    /** @return: string representation of Key-Value pairs in Map. */
    virtual std::string toString(void) const {
        stringstream ss;
        ss << numItems << "/" << max_size_ << endl;

        for (size_t i = 0; i < max_size_; i++) {
            if (myPairs[i].first != K()) {
                ss << "  [" << i << ":" << myPairs[i].first << "->" << myPairs[i].second << "]" << endl;
            }
        }
        return ss.str();
    }

    friend std::ostream &operator<<(std::ostream &out, const HashMap<K, V> &mapOutput) {
        for (size_t i = 0; i < mapOutput.capacity; i++) {
            out << endl << " #" << i << "=>" << " " << mapOutput.myPairs[i].first << ":" << mapOutput.myPairs[i].second;
        }
        return out;
    }
};

#endif //HASHMAP_H
