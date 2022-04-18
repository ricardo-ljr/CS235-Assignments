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
#include <string>
#include<algorithm>
#include "QS.h"

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

    QS<int> qs;
    int value, value1, value2, numbers, median1, median2, part1, part2, part3;
    string line, command;
    while (getline(in, line)) {

        try {
            if (line.size() == 0) continue;

            istringstream iss(line);
            iss >> command;
            if (command == "QuickSort") {
                out << line;
                iss >> value;
                if (qs.createArray(value)) {
                    out << " OK" << endl;
                } else {
                    out << " Error" << endl;
                }
                continue;
            } else if (command == "Capacity") {
                out << line;
                out << " " << qs.capacity() << endl;
                continue;
            } else if (command == "AddToArray") {
                out << command << "  ";
                string delim = "";
                while (iss >> numbers) {
                    qs.addElement(numbers);
                    out << delim <<  numbers;
                    delim = ",";
                }
                out << " OK" << endl;
                continue;
            } else if (command == "Clear") {
                out << line;
                qs.clear();
                out << " OK" << endl;
                continue;
            } else if (command == "Size") {
                out << line << " ";
                out << qs.size() << endl;
                continue;
            } else if (command == "Sort") {
                out << command << " ";
                iss >> value1 >> value2;
                out << value1 << "," << value2;
                if (qs.sort(value1, value2)) out << " OK";
                else out << " Error";
                out << endl;
                continue;
            } else if (command == "SortAll") {
                out << line;
                if (qs.sortAll()) {
                    out << " OK" << endl;
                } else {
                    out << " Error" << endl;
                }
                continue;
            } else if (command == "MedianOfThree") {
                string newLine = line.substr(0, 14);
                out << newLine;
                iss >> median1 >> median2;
                out << median1 << "," << median2;
                out << " = ";
                out << qs.medianOfThree(median1, median2);
                out << endl;
                continue;
            } else if (command == "Partition") {
                string newLine = line.substr(0, 9);
                out << newLine << " ";
                iss >> part1 >> part2 >> part3;
                out << part1 << "," << part2 << "," << part3;
                out << " = ";
                out << qs.partition(part1, part2, part3);
                out << endl;
                continue;
            } else if (command == "PrintArray") {
                out << line << " ";
                out << qs.toString();
                out << endl;
                continue;
            } else if (command == "Stats") {
                out << line;
                out << " " << qs.getComparisons() << "," << qs.getExchanges() << endl;
                continue;
            } else {
                out << "Invalid command" << endl;
            }
        }
        catch (std::exception &e) {
            out << e.what() << endl;
        }
    }

    return 0;
}
