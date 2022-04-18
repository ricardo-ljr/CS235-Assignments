

#ifndef QS_H
#define QS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "QSInterface.h"

using namespace std;

template<typename T>
class QS : public QSInterface<T> {
private:

    size_t capacityArray;
    size_t count; // number of items
    size_t swaps;
    size_t comparisons;
    T *data;

public:
    QS(void) {
        capacityArray = 0;
        count = 0;
        data = NULL;
        swaps = 0;
        comparisons = 0;
    }

    ~QS() { clear(); delete[] data; }

    /** Add an element to the QuickSort array. Dynamically grow array as needed. */
    virtual bool addElement(T element) {
        if (count == capacityArray) {
            reallocate();
        }

        if (count < capacityArray) {
            data[count] = element;
            count++;
            return true;
        } else return false;
    }

    void reallocate() {
        size_t newCapacity = capacityArray * 2;

        T *newData = new T[newCapacity];

        for (unsigned i = 0; i < capacityArray; i++) {
            newData[i] = data[i];
        }

        capacityArray = newCapacity;
        std::swap(data, newData);
        delete[] newData;
    }

    bool createArray(int capacity) {

        if (capacity != 0) {
            delete[] data;
        }

        if (capacity > 0) {
            data = new T[capacity];
            capacityArray = capacity;
            count = 0;

//            set current number of elements to 0;

            for (size_t i = 0; i < capacityArray; i++) {
                data[i] = 0;
            }

            return true;
        }
        return false;
    }

    /** Sort the elements of a QuickSort subarray using median and partition functions. */
    virtual bool sort(size_t left, size_t right) {
        if (right - left > 1) {
            int pivotIndex = medianOfThree(left, right);
            int newPivot = partition(left, right - 1, pivotIndex);
            if (newPivot == -1) return false;
            sort(left, newPivot);
            comparisons++;
            sort(newPivot + 1, right);
            comparisons++;
            return true;
        } else return false;
    }

    /** Sort all elements of the QuickSort array using median and partition functions. */
    virtual bool sortAll() {
        comparisons = 0;
        swaps = 0;
        return sort(0, count);
    }

    /** Removes all items from the QuickSort array. */
    virtual bool clear() {
        count = 0; // setting number of elements to 0
        for (size_t i = 0; i < capacityArray; i++) {
            data[i] = 0;
        } // deleting all the data
    }

    /** Return size of the QuickSort array. */
    virtual size_t capacity() const {
        return capacityArray;
    }

    /** Return number of elements in the QuickSort array. */
    virtual size_t size() const {
        return count;
    }

    size_t getComparisons() {
        return comparisons;
    }

    size_t getExchanges() {
        return swaps;
    }

    virtual int medianOfThree(size_t left, size_t right) {

        if (data == NULL || left < 0 || left >= capacityArray || right > capacityArray - 1 || left >= right) {
            comparisons++;
            return -1;
        }

        int mid = (left + right) / 2;
        right = right - 1;
        int temp1 = data[left];
        int temp2 = data[mid];
        int temp3 = data[right];


        if (temp2 < temp1) {
            comparisons++;
            data[left] = temp2;
            data[mid] = temp1;
            swaps++;
            temp1 = data[left];
            temp2 = data[mid];
            temp3 = data[right];
        }

        if (temp3 < temp2) {
            comparisons++;
            data[mid] = temp3;
            data[right] = temp2;
            swaps++;
            temp1 = data[left];
            temp2 = data[mid];
            temp3 = data[right];
        }

        if (temp2 < temp1) {
            comparisons++;
            data[left] = temp2;
            data[mid] = temp1;
            swaps++;
        }
        comparisons++;
        return mid;
    }

    virtual int partition(size_t left, size_t right, size_t pivotIndex) {

        if (data == NULL || left < 0 || right > count || right < 0 ||
            pivotIndex >= right || pivotIndex <= left) {
            comparisons++;
            return -1;
        }

//        Swap left with pivot index beginning

        std::swap(data[left], data[pivotIndex]);

//        Start partition here
        T i = left + 1; // up
        T j = right - 1; // down

        do {
            while ((data[i] <= data[left]) && (i != right - 1)) {
                i++;
                comparisons++;
            }

            while ((data[j] > data[left]) && (j != left)) {
                j--;
                comparisons++;
            }

            if (i < j) {
                std::swap(data[i], data[j]);
            }

            comparisons++;
            swaps++;

        } while (i < j);
        std::swap(data[j], data[left]);
        return j;
    }

    virtual std::string toString() const {
        stringstream out;
        string delim = "";
        if (count == 0) {
            out << "Empty" << endl;
        }

        for (size_t i = 0; i < count; i++) {
            out << delim << data[i];
            delim = ",";
        }

        return out.str();
    }

    friend ostream &operator<<(ostream &os, const QS<T> &qs) {
        os << qs.toString();
        return os;
    } // end operator<<
};

#endif //QS_H
