
#ifndef SNAP_H
#define SNAP_H

#include <vector>
#include <sstream>
#include "CR.h"
#include "CDH.h"

using namespace std;

class Student : public CDH {

private:
    string studentName;
    string studentId;
    string studentAddress;
    string studentPhone;

public:

    Student() {};

    Student(string name, string ID, string address, string phone){
        this->studentName = name;
        this->studentId = ID;
        this->studentAddress = address;
        this->studentPhone = phone;
    };

    ~Student() {};

    void setName(string name) {
        studentName = name;
    };

    string getName(void) const {
        return studentName;
    };

    void setID(string ID) {
        studentId = ID;

    }

    string getID() const {
        return studentId;
    }

    void setAddress(string address) {
        studentAddress = address;

    }

    string getAddress() const {
        return studentAddress;
    }

    void setPhone(string phone) {
        studentPhone = phone;

    }

    string getPhone() const {
        return studentPhone;
    }


    string toString() const {
        stringstream out;
        out << "snap(" << getID() << "," << getName() << "," << getAddress() << "," << getPhone() << ")";
        return out.str();
    }

    string toString2() const {
        stringstream out;
        out << getName() << ", " << getID() << ", " << getAddress() << ", " << getPhone() << endl;
        return out.str();
    }

    friend std::ostream &operator<<(ostream &os, const Student &student) {
        os << student.toString();
        return os;
    }

};


#endif //SNAP_H
