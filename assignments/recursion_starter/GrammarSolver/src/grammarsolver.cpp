/*
 * File: grammarsolver.cpp
 * --------------------------
 * Name:
 * Section leader:
 * This file contains grammar generating code for CS106B.
 */

#include "grammarsolver.h"
#include "map.h"
#include "simpio.h"

using namespace std;

/**
 * Generates grammar for a given symbol a certain number of times given
 * a BNF input file.
 *
 * This will be called by grammarmain.cpp.
 *
 * @param input - Input stream of BNF file.
 * @param symbol - Symbol to generate
 * @param times - Number of times grammar is generated
 * @return Vector of strings of size times with random generations of symbol
 */


string vector2string(Vector<string>& vector) {
    string output = "";
    for (string s : vector) {
        output = output + s + " ";
    }
    return output;
}

bool if_terminal(Map<string, Map<int, Vector<string>>>& dict, string symbol) {
    return !dict.containsKey(symbol);
}

Vector<string> helper(Map<string, Map<int, Vector<string>>>& dict, string symbol){
    Vector<string> output;
    if (if_terminal(dict, symbol)) {
        output.add(symbol);
        return output;
    }
    int random_index = randomInteger(0, dict[symbol].size()-1);
    Vector<string> components = dict[symbol][random_index];
    for (string& s : components) {
        output = output + helper(dict, s);
    }
    return output;
}

void readBNF(string& line, Map<string, Map<int, Vector<string>>>& dict) {
    Vector<string> first_split = stringSplit(line, "::=");
    Vector<string> second_split;
    int loc = 0;
    second_split = stringSplit(first_split[1], "|");
    for (string& s : second_split) {
        for (string val : stringSplit(s, " ")) {
            dict[first_split[0]][loc].add(val);
        }
        loc++;
    }
}

Vector<string> grammarGenerate(istream& input, string symbol, int times) {
    // TODO: write this function
    string line;
    string last_line = "";
    Map<string, Map<int, Vector<string>>> dict;
    getLine(input, line);
    while (line != last_line) {
        last_line = line;
        readBNF(line, dict);
        getLine(input, line);
    }
    Vector<string> output;
    for (int i = 0; i < times; i++) {
        Vector<string> time = helper(dict, symbol);
        output.add(vector2string(time));
    }
    return output;
}
