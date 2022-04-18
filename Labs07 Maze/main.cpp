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
#include "Maze.h"

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


    string line, item;
    int height, width, layers, value;
    getline(in, line);
    istringstream iss(line);
    iss >> height >> width >> layers;

    Maze maze(height, width, layers);

    for (size_t l = 0; l < layers; ++l) {
        in.ignore();
        for (int i = 0; i < height; ++i) {
            getline(in, line);
            istringstream iss(line);
            for (int j = 0; j < width; ++j) {
                iss >> value;
                maze.setValue(i, j, l, value);
            }
        }
    }

    out << "Solve Maze: " << endl;
    out << maze.toString();

    bool finalSolution = maze.find_maze_path();

    if (finalSolution) {
        out << endl << "Solution: " << endl;
        out << maze.toString();
    } else {
        out << endl << "No Solution Exists!";
    }
    return 0;
}
