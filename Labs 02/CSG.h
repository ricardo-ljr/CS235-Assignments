

#ifndef CSG_H
#define CSG_H

#include <string>
#include <iostream>
#include <sstream>
#include "Snap.h"

Student stu;

using namespace std;

class CSG {
private:

    string studentId;
    string grade;
    string courseName;

public:

    CSG() {};

    CSG( string studentId, string grade, string name) {
        setID(studentId);
        setCourseName(name);
        setGrade(grade);
    }

    ~CSG() {}

    void setID(string ID) {
        studentId = ID;

    }

    string getID() const {
        return studentId;
    }

    void setGrade(string grades) {
        grade = grades;
    }

    string getGrade(void) const {
        return grade;
    }

    void setCourseName(string course) {
        courseName = course;
    }

    string getCourseName() const {
        return courseName;
    }

    string toString() const {
        stringstream out;
        out << "csg(" << getCourseName() << "," << getID() << "," << getGrade() << ")";
        return out.str();
    }

    string toString2() const {
        stringstream out;
        out << getCourseName() << "," << stu.getName()  << "," << getGrade() << endl;
        return out.str();
    }

    friend std::ostream &operator<<(ostream &os, const CSG &student) {
        os << student.toString();
        return os;
    }

};

#endif //CSG_H
