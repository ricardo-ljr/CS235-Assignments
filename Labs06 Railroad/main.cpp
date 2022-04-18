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
#include "Station.h"
#include "Deque.h"

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

    Station<string> train;
    string line, command, item2, value;
    while (getline(in, line)) {

        try {
            if (line.size() == 0) continue;

            istringstream iss(line);
            iss >> command;
            if (command == "Add:station") {
                out << line;
                iss >> item2;
                out << train.addCar(item2);
                continue;
            } else if (command == "Add:queue") {
                out << line;
                out << train.addToQueue();
                continue;
            } else if (command == "Add:stack") {
                out << line;
                out << train.addToStack();
                continue;
            }else if (command == "Remove:station") {
                out << line;
                out << train.removeCar();
                continue;
            } else if (command == "Remove:queue") {
                out << line;
                out << train.removeFromQueue();
                continue;
            } else if (command == "Remove:stack") {
                out << line;
                out << train.removeFromStack();
                continue;
            } else if (command == "Top:station") {
                out << line;
                out << train.topStation();
                continue;
            } else if (command == "Top:queue") {
                out << line;
                out << train.topQueue();
                continue;
            } else if (command == "Top:stack") {
                out << line;
                out << train.topStack();
                continue;
            } else if (command == "Size:queue") {
                out << line;
                out << train.sizeQueue();
                continue;
            } else if (command == "Size:stack") {
                out << line;
                out << train.stackSize();
                continue;
            } else if (command == "Size:train") {
                out << line;
                out << train.sizeVector();
                continue;
            } else if (command == "Queue") {
                out << line;
                out << train.printQueue();
                continue;
            } else if (command == "Stack") {
                out << line;
                out << train.printStack();
                continue;
            } else if (command == "Train") {
                out << line << " ";
                out << train.printTrainVector();
                out << endl;
                continue;
            } else if (command == "Find") {
                out << line;
                iss >> value;
                out << train.find(value);
                continue;
            }
        }
        catch (std::exception& e) {
            out << e.what() << endl;
        }
    }


    return 0;
}
