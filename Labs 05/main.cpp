#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK ;
#endif

#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include "ExpressionManager.h"

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

    ExpressionManager expression;
    string line, command, infix, post;
    while (getline(in, line)) {

        try {
            if (line.size() == 0) continue;

            istringstream iss(line);
            iss >> command;
            if (command == "Expression:") {
                out << endl << line << endl;
                infix = line.substr(12, line.length());
                expression.setExpression(infix);
                continue;
            } else if (command == "Infix:") {
                out << command << " ";
                out << expression.infix() << endl;
                continue;
            } else if (command == "Postfix:") {
                out << line << " ";
                post = expression.postfix();
                expression.setPostFix(post);
                out << post << endl;
            } else if (command == "Value:") {
                out << line << " ";
                out << expression.postfixEvaluate(post) << endl;
                continue;
            } else if (command == "Prefix:") {
                out << command << " " << endl;
                continue;
            }
        }
        catch (std::exception &e) {
            out << e.what() << endl;
        }
    }


    return 0;
}
