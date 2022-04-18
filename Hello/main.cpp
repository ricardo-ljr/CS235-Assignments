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
#include "LinkedListInterface.h"
#include "LinkedList.h"

using namespace std;

int main(int argc, char *argv[]) {

    VS_MEM_CHECK;

//    Open input and output files

    if (argc < 3)
    {
        cerr << "Please provide name of input and output files";
        return 1;
    }
    cout << "Input file: " << argv[1] << endl;

//    Input file name
    ifstream in(argv[1]);
    if (!in)
    {
        cerr << "Unable to open " << argv[1] << " for input";
        return 2;
    }
    cout << "Output file: " << argv[2] << endl;

//    Output file name
    ofstream out(argv[2]);
    if (!out)
    {
        in.close();
        cerr << "Unable to open " << argv[2] << " for output";
        return 3;
    }

    LinkedList<string> linkedList;
    string line, first, item, item2, find_value, after_value, before_value, value, old_value, new_value;
    while (getline(in, line)) {
        try {
            istringstream iss(line);
            iss >> first;
            if (first == "Insert") {
                out << "Insert " << line.substr(7);
                istringstream  iss(line.substr(7));
                while (iss >> item) {
                    linkedList.push_front(item);
                }
                out << endl;
                continue;
            }
            else if (first == "PrintList") {
                out << "PrintList " << linkedList << endl;
                continue;
            }
            else if (line == "Clear") {
                linkedList.clear();

                out << "Clear OK" << endl;
                continue;
            }
            else if (first == "Iterate") {
                LinkedList<string>::Iterator iter = linkedList.begin();
                out << "Iterate";
                if (linkedList.size() == 0) {
                    out << " Empty!" << endl;
                } else {
                    while (iter != linkedList.end()) {
                        out << endl << " [" << *iter << "]";
                        ++iter;
                    }
                    out << endl;
                }
                continue;
            } else if (first == "Find") {
                iss >> item2;
                LinkedList<string>::Iterator position = linkedList.find(linkedList.begin(), linkedList.end(), item2);
                istringstream  iss(line.substr(5));
                out << "Find ";
                out << item2;
                if (position != linkedList.end()) {
                    out << " OK" << endl;
                } else {
                    out << " Not Found" << endl;
                }

                continue;
            }

            else if (first == "InsertAfter") {
                iss >> after_value >> find_value;
                LinkedList<string>::Iterator position = linkedList.find(linkedList.begin(), linkedList.end(), find_value);

                out << "InsertAfter ";
                out << after_value << " " << find_value;
                if (position != linkedList.end()) {
                    out << " OK" << endl;
                    linkedList.insert_after(position, after_value);
                } else {
                    out << " Not Found" << endl;
                }

                continue;

            } else if (first == "InsertBefore") {
                iss >> before_value >> find_value;
                LinkedList<string>::Iterator position = linkedList.find(linkedList.begin(), linkedList.end(), find_value);

                istringstream iss(line.substr(13));
                out << "InsertBefore ";
                out << before_value << " " << find_value;
                if (position != linkedList.end()) {
                    out << " OK" << endl;
                    linkedList.insert(position, before_value);
                } else {
                    out << " Not Found" << endl;

                }

                continue;
            } else if (first == "Erase") {
                iss >> value;
                LinkedList<string>::Iterator position = linkedList.find(linkedList.begin(), linkedList.end(), value);

                out << "Erase ";
                out << value;
                if (position != linkedList.end()) {
                    out << " OK" << endl;
                    linkedList.erase(position);
                } else {
                    out << " Not Found" << endl;
                }
                continue;
            } else if (first == "Replace") {
                iss >> old_value >> new_value;
                linkedList.replace(linkedList.begin(), linkedList.end(), old_value, new_value);

                out << "Replace " << old_value << " " << new_value << " OK" << endl;
            }
            else {
                out << "Invalid line: " << line << endl;
            }
        }
        catch (string& es) {
            cout << es;
        }

    }
    return 0;
}
