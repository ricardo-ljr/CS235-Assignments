#include<iostream>
#include <fstream>
#include <string>
#include <typeinfo>
#include<vector>
#include <iomanip>
using namespace std;

string getGrade(double score,double average);

int main(int argc, char *argv[]){
    fstream newfile;
    int num_students,num_exams;
    vector<string> splitted;
    string *names;
    double** scores;
    int** c;
    string** grades;

    newfile.open(argv[1]);
    if (newfile.is_open()){
      string tp,name;
      int i=0;
      while(getline(newfile, tp)){
         if(i == 0){

            num_students = stoi(splitted[0]);
            num_exams = stof (splitted[1]);
            names = new string[num_students];
            int rows = num_students, cols = num_exams;
            scores = new double*[rows];

            for(int k = 0; k < rows; ++k){
                scores[k] = new double[cols];}

            grades = new string*[rows];

            for(int k = 0; k < rows; ++k){
                grades[k] = new string[cols];}
         }

         if(i!=0){
             name = splitted[0] + " " + splitted[1];
             names[i-1] = name;

             double sum = 0.0, average = 0.0;

             for(int j = 3;j < num_exams + 3; j++){
                 scores[i-1][j-3] = atof(splitted.at(j).c_str());
             }
        }        
         i = i + 1;
    }
    newfile.close(); //close the file object.

    ofstream newfile;

    newfile.open(argv[2], ios::out);
    if(newfile.is_open()){
        //student scores
        newfile << "Student Scores: \n";
        for(int i = 0;i<num_students;i++){
            newfile << right << setw(20) << names[i]; //<<"\t";//right<<setw(7);
            for(int j=0;j<num_exams;j++){
                newfile << right << setw(6) << scores[i][j] << " \n"[j == num_exams-1];
            }
        }
        //average for each exam:
        double avg[num_exams];
        newfile << "Exam Averages: \n";
        for(int j = 0;j <num_exams; j++){
            newfile << "\t"<<"Exam "<< j + 1 << " Average = ";
            double sum = 0, average;
            for(int i = 0;i < num_students; i++){
                sum = sum + scores[i][j];
            }

            average = sum/num_students;
            avg[j] = average;
            newfile << right << setw(7) << setprecision(3) << average<<"\n";
        }
        //score grades
        newfile << "Student Exam Grades: \n";
        for(int i = 0;i < num_students; i++){
            newfile << right << setw(20) << names[i];
            for(int j = 0; j < num_exams; j++){
                newfile << right << setw(7) << scores[i][j] << "(" << getGrade(scores[i][j], avg[j]) << ")" << " \n"[j == num_exams-1];
                grades[i][j] = getGrade(scores[i][j], avg[j]);
            }
        }
        //grade num:
        newfile << "Exam Grades: \n";
        string g = {'A','B','C','D','E'};
        int c[8][5];
        for(int k = 0; k < 5; k++){
        int count_[8];
        for(int j = 0;j < num_exams; j++){
            string temp = "";
            for(int i=0;i<num_students;i++){
                temp = temp + grades[i][j];
            }

        count_[j] = count(temp.begin(),temp.end(),g[k]);
        }
        for(int l = 0; l < 8; l++){
            c[l][k]=count_[l];
        }
        }            
        for (int i = 0; i < 8; i++){ 
            newfile << "\t" << "Exam" << "\t" << i + 1;
        for (int j = 0; j < 5; j++) 
            newfile << right << setw(7) << c[i][j] << "(" << g[j] << ")" << " \n"[j == 5-1];
        }
    //final grade:
        newfile << "Student Final Grades: \n";
        double class_avg = 0;
        double avg_[num_students];
        for(int i = 0;i < num_students; i++){
            double sum = 0,average;
            for(int j = 0;j < num_exams; j++){
                sum = sum+scores[i][j];
            }
            average = sum/num_exams;
            avg_[i] = average;
            class_avg = class_avg+average;
        }
        class_avg=class_avg/num_students;
        for(int i = 0; i < num_students; i++){
            newfile << right<<setw(20) << names[i] << right << setw(7) << setprecision(3) << avg_[i] << "(" << getGrade(avg_[i], class_avg) << ")" <<endl;
        }
        newfile << right << setw(20) << "Class Average" << right << setw(7) << setprecision(3) << class_avg << endl;

      newfile.close(); //close the file object
   }
}

    return 0;
}

string getGrade(double score, double average){
    string grade;
    if( score >= (average-5) && score<=(average+5)) {
        //cout<<average-5;
        grade = "C";
    }
    else if(score>(average+5) && score<(average+15)){
        grade = "B";
    }
    else if(score>=(average-15) && score<(average-5)){
        grade = "D";
    }
    else if(score<(average-15)){
        grade = "E";
    }
    else if(score>=(average+15)){
        grade = "A";
    }
    cout << "Score: " << score << ", Avg : " << average << endl;
    return grade;

}