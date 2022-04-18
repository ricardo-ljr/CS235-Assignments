#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK ;
#endif


#include<iostream>
#include <fstream>
#include <string>
#include <typeinfo>
#include <iomanip>

using namespace std;

string getGrade(double score, double average);

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

    string firstName, lastName;
    int numberStudents, numberExams, testScore;

    in >> numberStudents >> numberExams;

    out << "Student Scores: " << endl;

    string *studentNames = new string[numberStudents];
    int **arrayScores = new int *[numberStudents];

    for (int i = 0; i < numberStudents; i++) {
        in >> firstName >> lastName;
        out << fixed << setw(10) << " " << firstName << " " << lastName << " " << setw(10);
        studentNames[i] = firstName + " " + lastName;
        arrayScores[i] = new int[numberExams];
        for (int j = 0; j < numberExams; j++) {
            in >> testScore;
            arrayScores[i][j] = testScore;
            out << arrayScores[i][j] << " ";
        }
        out << endl;
    }

    double *testAverages = new double[numberExams];
    double total = 0.0;

    out << "Exam Averages:" << endl;

    for (int i = 0; i < numberExams; i++) {

        for (int j = 0; j < numberStudents; j++) {
            total += arrayScores[j][i];
        }
        testAverages[i] = total / numberStudents;
        out << "\tExam " << i + 1 << " Average = " << setprecision(1) << testAverages[i] << endl;
        total = 0.0;
    }

    out << "Student Exam Grades: " << endl;

    string letterGrade;
    int **examGrades = new int *[numberExams];

    for (int i = 0; i < numberExams; i++) {
        examGrades[i] = new int[5];
        for (int j = 0; j < 5; j++) {
            examGrades[i][j] = 0;
        }
    }


    for (int i = 0; i < numberStudents; i++) {
        out << "\t" << studentNames[i] << "\t";
        for (int j = 0; j < numberExams; j++) {
            out << arrayScores[i][j];
            if (arrayScores[i][j] - testAverages[j] >= 15) {
                letterGrade = "A";
                examGrades[j][0]++;
            } else if (arrayScores[i][j] - testAverages[j] <= -15) {
                letterGrade = "E";
                examGrades[j][4]++;
            } else if (arrayScores[i][j] - testAverages[j] > 5 && arrayScores[i][j] - testAverages[j] < 15) {
                letterGrade = "B";
                examGrades[j][1]++;
            } else if (arrayScores[i][j] - testAverages[j] < -5 && arrayScores[i][j] - testAverages[j] > -15) {
                letterGrade = "D";
                examGrades[j][3]++;
            } else if (arrayScores[i][j] - testAverages[j] >= -5 || arrayScores[i][j] - testAverages[j] >= 5) {
                letterGrade = "C";
                examGrades[j][2]++;
            }

            out << "(" << letterGrade << ") ";

        }
        out << endl;
    }


    out << "Exam Grades: " << endl;

    for (int i = 0; i < numberExams; i++) {
        out << "\tExam  " << i + 1 << " " << examGrades[i][0] << "(A) " << examGrades[i][1] << "(B) "
            << examGrades[i][2] << "(C) " << examGrades[i][3]
            << "(D) " << examGrades[i][4] << "(E)" << endl;
    }

    double classAverage = 0.0;
    double averageTotal = 0.0;
    double classTotal = 0.0;
    double *studentAverage = new double[numberStudents];

    for (int i = 0; i < numberStudents; i++) {
        for (int j = 0; j < numberExams; j++) {
            averageTotal += arrayScores[i][j];
        }
        studentAverage[i] = averageTotal / numberExams;
        averageTotal = 0.0;
    }
    for (int i = 0; i < numberStudents; i++) {
        classTotal += studentAverage[i];
    }
    classAverage = classTotal / numberStudents;

    out << "Student Final Grades: " << endl;

    for (int i = 0; i < numberStudents; i++) {
        if (studentAverage[i] - classAverage >= 15) {
            letterGrade = "A";
        } else if (studentAverage[i] - classAverage <= -15) {
            letterGrade = "E";
        } else if (studentAverage[i] - classAverage > 5 && studentAverage[i] - classAverage < 15) {
            letterGrade = "B";
        } else if (studentAverage[i] - classAverage < -5 && studentAverage[i] - classAverage > -15) {
            letterGrade = "D";
        } else if (studentAverage[i] - classAverage >= -5 || studentAverage[i] - classAverage >= 5) {
            letterGrade = "C";
        }
        out << "\t" << studentNames[i] << " " << studentAverage[i] << "(" << letterGrade << ")" << endl;
    }

    out << "Class Average Score = " << classAverage;


    for (int i = 0; i < numberExams; i++) {
        delete[] examGrades[i];
    }
    delete[] examGrades;
    delete[] testAverages;
    for (int i = 0; i < numberStudents; i++) {
        delete[] arrayScores[i];
    }
    delete[] arrayScores;
    delete[] studentNames;
    delete[] studentAverage;


    return 0;
}