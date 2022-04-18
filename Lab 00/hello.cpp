#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

int main(int argc, char *argv[])
{
    VS_MEM_CHECK // enable check for memory leaks

        // open argv[1] or cin for input
        istream &in = (argc > 1) ? *(new ifstream(argv[1])) : cin;
    if (!in)
        return 1;

    // open argv[2] or cout for output
    ostream &out = (argc > 2) ? *(new ofstream(argv[2])) : cout;
    if (!out)
        return 2;

    // read input file lines and send to output file
    for (string line; getline(in, line);)
    {
        out << line << endl;
    }

    // **LEAK SOME MEMORY**
    // int *memory = new int(100);

    // recover input/output object memory
    if (&in != &cin)
        delete (&in);
    if (&out != &cout)
        delete (&out);

    return 0;
}