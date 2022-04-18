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
#include "BST.h"
#include "BTNODE.h"

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

    BST<int> bst_int;
    BST<string> bst_string;
    bool integer;
    int number;
    string value;
    string line, item, command;
    while (getline(in, line)) {
        try {
            if (line.size() == 0) {
                continue;
            }
            istringstream iss(line);
            iss >> command;
            if (command == "INT") {
                integer = true;
                out << line << " true" << endl;
            } else if (command == "add") {
                if (integer) {
                    out << line << " ";
                    iss >> number;
                    if (bst_int.addNode(number)) {
                        out << "true" << endl;
                    } else {
                        out << "false" << endl;
                    }
                } else {
                    out << line << " ";
                    iss >> value;
                    if (bst_string.addNode(value)) {
                        out << "true" << endl;
                    } else {
                        out << "false" << endl;
                    }
                }
            } else if (command == "print") {
                if (integer) {
                    out << line << ":";
                    out << bst_int.toString();
                    out << endl;
                } else {
                    out << line << ":";
                    out << bst_string.toString();
                    out << endl;
                }

            } else if (command == "STRING") {
                integer = false;
                out << line << " true" << endl;
            } else if (command == "remove") {
                if (integer) {
                    out << line;
                    iss >> number;
                    if (bst_int.removeNode(number)) {
                        out << " true" << endl;
                    } else {
                        out << " false" << endl;
                    }
                } else {
                    out << line;
                    iss >> value;
                    if (bst_string.removeNode(value)) {
                        out << " true" << endl;
                    } else {
                        out << " false" << endl;
                    }
                }
            } else if (command == "clear") {
                if (integer) {
                    out << line;
                    bst_int.clearTree();
                    if (bst_int.clearTree()) {
                        out << " true";
                    }
                    out << endl;
                } else {
                    out << line;
                    bst_string.clearTree();
                    if (bst_string.clearTree()) {
                        out << " true";
                    }
                    out << endl;
                }
            } else if (command == "size") {
                if (integer) {
                    out << line;
                    out << " " << bst_int.size();
                    out << endl;
                } else {
                    out << line;
                    out << " " << bst_string.size();
                    out << endl;
                }

            } else if (command == "find") {
                if (integer) {
                    out << line;
                    iss >> number;
                    if (bst_int.find(number)) {
                        out << " found" << endl;
                    } else {
                        out << " not found" << endl;
                    };
                } else {
                    out << line;
                    iss >> value;
                    if (bst_string.find(value)) {
                        out << " found" << endl;
                    } else {
                        out << " not found" << endl;
                    };
                }
            } else if (command == "tree") {
                out << line << ":" << endl;
            } else {
                out << "Invalid operation" << endl;
            }
        }
        catch (string &es) {
            cout << es;
        }
    }

    bst_int.clearTree();
    bst_string.clearTree();

    return 0;
}
