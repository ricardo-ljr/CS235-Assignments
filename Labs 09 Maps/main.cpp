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
#include <algorithm>
#include "Set.h"
#include "HashMap.h"

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

    Set<string> set;
    HashMap<string, string> myHashMapPokemon;
    HashMap<string, string> myHashMapMoves;
    HashMap<string, Set<string>> effective;
    HashMap<string, Set<string>> ineffective;

    string line, item, command, newLine, values, pokemon, type, move, moveType, item1, item2, item3, item4, item5;

    while (getline(in, line)) {
        if (line.size() == 0) continue;
        istringstream iss(line);
        iss >> command;
        if (command == "Set:") {
            out << line << endl;
            iss >> values;
            if (set.insert(values))

                while (iss >> values) {
                    set.insert(values);
                }
            out << "  [" << set.toString() << "]";
            out << endl << endl;
            set.clear();
        } else if (command == "Pokemon:") {
            out << line << endl;
            iss >> pokemon >> type;
            myHashMapPokemon[pokemon] = type;
        } else if (command == "Move:") {
            out << line << endl;
            iss >> move >> moveType;
            myHashMapMoves[move] = moveType;
        } else if (command == "Pokemon") {
            out << endl << line << ": ";
            out << myHashMapPokemon.toString();
        } else if (command == "Moves") {
            out << endl << line << ": ";
            out << myHashMapMoves.toString();
        } else if (command == "Effective:") {
            iss >> item2;
            out << command << " " << item2;
            while (iss >> item3) {
                effective[item2].insert(item3);
                out << " " << item3;
            }
            out << endl;
        } else if (command == "Effectivities") {
            out << endl << command << ": " << effective.toString() << endl;
        } else if (command == "Ineffective:") {
            iss >> item2;
            out << command << " " << item2;
            while (iss >> item3) {
                ineffective[item2].insert(item3);
                out << " " << item3;
            }
            out << endl;
        } else if (command == "Ineffectivities") {
            out << command << ": " << ineffective.toString() << endl;
        } else if (command == "Battle:") {
            out << command << " ";
            iss >> item2;
            iss >> item3;
            iss >> item4;
            iss >> item5;
            string pokemonA = item2, pokemonB = item4, attackA = item3, attackB = item5;
            int damage1To2 = effective[myHashMapMoves[attackA]].count(myHashMapPokemon[pokemonB]) -
                             ineffective[myHashMapMoves[attackA]].count(myHashMapPokemon[pokemonB]);
            int damage2To1 = effective[myHashMapMoves[attackB]].count(myHashMapPokemon[pokemonA]) -
                             ineffective[myHashMapMoves[attackB]].count(myHashMapPokemon[pokemonA]);

            out << pokemonA << " " << attackA << " " << pokemonB << " " << attackB << endl;
            out << "  " << pokemonA << " (" << attackA << ") vs " << pokemonB << " (" << attackB << ")" << endl;
            out << "  " << pokemonA << " is a " << myHashMapPokemon[pokemonA] << " type Pokemon." << endl;
            out << "  " << pokemonB << " is a " << myHashMapPokemon[pokemonB] << " type Pokemon." << endl;
            out << "  " << attackA << " is a " << myHashMapMoves[attackA] << " type move." << endl;
            out << "  " << attackB << " is a " << myHashMapMoves[attackB] << " type move." << endl;
            out << "  " << attackA << " is super effective against [" << effective[myHashMapMoves[attackA]]
                << "] type Pokemon" << endl;
            out << "  " << attackA << " is ineffective against [" << ineffective[myHashMapMoves[attackA]]
                << "] type Pokemon." << endl;

            if (effective[myHashMapMoves[attackA]].findIndex(myHashMapPokemon[pokemonB])) {
                out << "  " << pokemonA << "'s " << attackA << " is super effective against " << pokemonB << endl;
            } else if (ineffective[myHashMapMoves[attackA]].findIndex(myHashMapPokemon[pokemonB])) {
                out << "  " << pokemonA << "'s " << attackA << " is ineffective against " << pokemonB << endl;
            } else {
                out << "  " << pokemonA << "'s " << attackA << " is effective against " << pokemonB << endl;
            }


            out << "  " << attackB << " is super effective against [" << effective[myHashMapMoves[attackB]]
                << "] type Pokemon." << endl;
            out << "  " << attackB << " is ineffective against [" << ineffective[myHashMapMoves[attackB]]
                << "] type Pokemon." << endl;

            if (effective[myHashMapMoves[attackB]].findIndex(myHashMapPokemon[pokemonA])) {
                out << "  " << pokemonB << "'s " << attackB << " is super effective against " << pokemonA << endl;
            } else if (ineffective[myHashMapMoves[attackB]].findIndex(myHashMapPokemon[pokemonA])) {
                out << "  " << pokemonB << "'s " << attackB << " is ineffective against " << pokemonA << endl;
            } else {
                out << "  " << pokemonB << "'s " << attackB << " is effective against " << pokemonA << endl;
            }

            if ((damage1To2 - damage2To1) < 0) /** pokemon A wins **/ {
                out << "  In the battle between " << pokemonA << " and " << pokemonB << ", " << pokemonB << " wins!"
                    << endl;
            } else if ((damage1To2 - damage2To1) > 0)  /** pokemon B wins */ {
                out << "  In the battle between " << pokemonA << " and " << pokemonB << ", " << pokemonA << " wins!"
                    << endl;
            } else /** It's a tie **/{
                out << "  The battle between " << pokemonA << " and " << pokemonB << " is a tie." << endl;
            }

            out << endl;
        } else {
            out << "Invalid command" << endl;
        }
    }

    return 0;
}
