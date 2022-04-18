#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK ;
#endif


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Snap.h"
#include "CSG.h"
#include "CDH.h"
#include "CR.h"

using namespace std;


int main(int argc, char *argv[]) {

    VS_MEM_CHECK;

//    Open input and output files

    if (argc < 3) {
        cerr << "Please provide name of input and output files";
        return 1;
    }
    cout << "Input file: " << argv[1] << endl;

//    Input file name
    ifstream in(argv[1]);
    if (!in) {
        cerr << "Unable to open " << argv[1] << " for input";
        return 2;
    }
    cout << "Output file: " << argv[2] << endl;

//    Output file name
    ofstream out(argv[2]);
    if (!out) {
        in.close();
        cerr << "Unable to open " << argv[2] << " for output";
        return 3;
    }

    vector<Student> student;
    vector<CSG> csg;
    vector<CDH> cdh;
    vector<CR> cr;
    Student stu;
    CSG grades;
    CR course;
    CDH days;


    string line, item;
    string studentID, studentName, studentAddress, studentPhone, studentGrade;
    out << "Input Strings:" << endl;
    while (getline(in, line)) {
        try {
            if (line.size() == 0) continue;


            if ("snap(" == line.substr(0, 5)) {
                out << line << endl;
//                snap(12345,Charlie Brown,Manager,555-1234).
                string studentID = line.substr(5, line.find(',') - 5);
                line = line.substr(line.find(',') + 1);
                stu.setID(studentID);
                string studentName = line.substr(0, line.find(','));
                stu.setName(studentName);
                line = line.substr(line.find(',') + 1);
                string studentAddress = line.substr(0, line.find(','));
                line = line.substr(line.find(',') + 1);
                stu.setAddress(studentAddress);
                string studentPhone = line.substr(0, line.find(')'));
                stu.setPhone(studentPhone);
                student.push_back(Student(studentName, studentID, studentAddress, studentPhone));

            } else if ("csg(" == line.substr(0, 4)) {
                out << line << endl;
                string courseName = line.substr(4, line.find(',') - 4);
                line = line.substr(line.find(',') + 1);
                string studentID = line.substr(0, line.find(','));
                line = line.substr(line.find(',') + 1);
                string studentGrade = line.substr(0, line.find(')'));
                grades.setGrade(studentGrade);
                csg.push_back(CSG(studentID, studentGrade, courseName));
            } else if ("cdh(" == line.substr(0, 4)) {
                out << line << endl;
                string courseName = line.substr(4, line.find(',') - 4);
                line = line.substr(line.find(',') + 1);
                string courseDay = line.substr(0, line.find(','));
                days.setDay(courseDay);
                line = line.substr(line.find(',') + 1);
                string courseTime = line.substr(0, line.find(')'));
                cdh.push_back(CDH(courseName, courseDay, courseTime));
            } else if ("cr(" == line.substr(0, 3)) {
                out << line << endl;
                string courseName = line.substr(3, line.find(',') - 3);
                course.setCourseName(courseName);
                line = line.substr(line.find(',') + 1);
                string courseRoom = line.substr(0, line.find(')'));
                course.setCourseRoom(courseRoom);
                cr.push_back(CR(courseName, courseRoom));

            } else {
                out << "**Error: " << line << endl;
            }
        }
        catch (string &es) {
            cout << es;
        }

    }

    out << endl << "Vectors:" << endl;

    for (unsigned int i = 0; i < student.size(); i++) {
        out << student[i] << endl;
    }

    for (unsigned int i = 0; i < csg.size(); i++) {
        out << csg[i] << endl;
    }

    for (unsigned int i = 0; i < cdh.size(); i++) {
        out << cdh[i] << endl;
    }

    for (unsigned int i = 0; i < cr.size(); i++) {
        out << cr[i] << endl;
    }

    out << "Course Grades:" << endl;

    for (unsigned int i = 0; i < student.size(); i++) {
        out << csg[i].getCourseName() << "," << student[i].getName() << "," << csg[i].getGrade() << endl;
    }

    out << endl << "Student Schedules:" << endl;

    for (unsigned int i = 0; i < student.size(); i++) {
        out << student[i].toString2();
        out << cdh[i].toString2() << endl;
    }


    return 0;
}
