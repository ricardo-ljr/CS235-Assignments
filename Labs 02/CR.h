
#ifndef CR_H
#define CR_H

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class CR {
private:
    string courseName;
    string courseRoom;
public:
    CR() {}

    CR(string courseName, string courseRoom) {
        setCourseName(courseName);
        setCourseRoom(courseRoom);
    }

    ~CR() {}

    void setCourseName(string name) {
        courseName = name;
    }

    string getCourseName() const {
        return courseName;
    }

    void setCourseRoom(string room) {
        courseRoom = room;
    }

    string getCourseRoom() const {
        return courseRoom;
    }

    string toString() const {
        stringstream out;
        out << "cr(" << getCourseName() << "," << getCourseRoom() << ")" << endl;
        return out.str();
    }

    friend std::ostream &operator<<(ostream &os, const CR &student) {
        os << student.toString();
        return os;
    }
};

#endif //CR_H
