

#ifndef MAZE_H
#define MAZE_H

#include "MazeInterface.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Maze : public MazeInterface {
private:
    int h = 0;
    int w = 0;
    int l = 0;
    int ***myArray;
    enum CellValue_t {
        OPEN, BLOCKED, VISITED, EXIT, LEFT, RIGHT, UP, DOWN, OUT, IN
    };
public:
    Maze(int height, int width, int layers) {
        this->h = height;
        this->w = width;
        this->l = layers;
        myArray = new int **[h];
        for (size_t i = 0; i < h; ++i) {
            myArray[i] = new int *[w];
            for (size_t j = 0; j < w; ++j) {
                myArray[i][j] = new int[l];
            }
        }
    }

    ~Maze(void) {
        for (size_t i = 0; i < h; i++) {
            for (size_t j = 0; j < w; j++)
                delete[] myArray[i][j];
            delete[] myArray[i];
        }
        delete[] myArray;
    };

    virtual void setValue(int height, int width, int layers, int value) {
        myArray[height][width][layers] = value;
    };

    virtual bool find_maze_path() {
        return rec_find_maze_path(0, 0, 0);
    };

    virtual std::string toString() const {
        std::stringstream out;

        for (int k = 0; k < l; ++k) {
            out << "Layer " << k + 1 << endl;

            for (int i = 0; i < h; ++i) {
                for (int j = 0; j < w; ++j) {
                    if (myArray[i][j][k] == OPEN) {
                        out << " _";
                    } else if (myArray[i][j][k] == BLOCKED) {
                        out << " X";
                    } else if (myArray[i][j][k] == VISITED) {
                        out << " *";
                    } else if (myArray[i][j][k] == EXIT) {
                        out << " E";
                    } else if (myArray[i][j][k] == LEFT) {
                        out << " L";
                    } else if (myArray[i][j][k] == RIGHT) {
                        out << " R";
                    } else if (myArray[i][j][k] == UP) {
                        out << " U";
                    } else if (myArray[i][j][k] == DOWN) {
                        out << " D";
                    } else if (myArray[i][j][k] == OUT) {
                        out << " O";
                    } else if (myArray[i][j][k] == IN) {
                        out << " I";
                    } else out << " " << myArray[i][j][k];
                }
                out << endl;
            }
        }
        return out.str();
    }


    bool rec_find_maze_path(int x, int y, int z);
};


bool Maze::rec_find_maze_path(int x, int y, int z) {
    if ((x < 0) || (x >= h) || (y < 0) || (y >= w) || (z < 0) || (z >= l)) {
        return false;
    }
    if (myArray[x][y][z] != OPEN) {
        return false;
    }
    if ((x == h - 1) && (y == w - 1) && (z == l - 1)) {
        myArray[x][y][z] = EXIT;
        return true;
    }

    myArray[x][y][z] = VISITED;

    if (rec_find_maze_path(x, y - 1, z)) {
        myArray[x][y][z] = LEFT;
        return true;
    }
    if (rec_find_maze_path(x, y + 1, z)) {
        myArray[x][y][z] = RIGHT;
        return true;
    }
    if (rec_find_maze_path(x - 1, y, z)) {
        myArray[x][y][z] = UP;
        return true;
    }
    if (rec_find_maze_path(x + 1, y, z)) {
        myArray[x][y][z] = DOWN;
        return true;
    }
    if (rec_find_maze_path(x, y, z - 1)) {
        myArray[x][y][z] = OUT;
        return true;
    }
    if (rec_find_maze_path(x, y, z + 1)) {
        myArray[x][y][z] = IN;
        return true;
    }
    return false;
}


#endif //MAZE_H
