
#ifndef CDH_H
#define CDH_H

#include <string>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class CDH {
private:
    string courseName;
    string day;
    string time;
public:

    CDH() {}

    CDH(string courseName, string day, string time) {
        setCourseName(courseName);
        setDay(day);
        setTime(time);
    }

    ~CDH() {}

    void setCourseName(string name) {
        courseName = name;
    }

    string getCourseName() const {
        return courseName;
    }

    void setDay(string days) {
        day = days;
    }

    string getDay() const {
        return day;
    }

    void setTime(string hour) {
        time = hour;
    }

    string getTime() const {
        return time;
    }

    string toString() const {
        stringstream out;
        out << "cdh(" << getCourseName() << "," << getDay() << "," << getTime() << ")";
        return out.str();
    }

    string toString2() const {
        stringstream out;
        out << "  " << getCourseName() << " " << getDay() << getDay() << " " << getTime() << " ";
        return out.str();
    }

    friend std::ostream &operator<<(ostream &os, const CDH &student) {
        os << student.toString();
        return os;
    }
};


#endif //LAB02_SNAP_CDH_H
