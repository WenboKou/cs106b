// This is a .h file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include "grid.h"
#include "lexicon.h"
using namespace std;

class Boggle {
public:
    Boggle(Lexicon& dictionary, string boardText = "");
    char getLetter(int row, int col);
    bool checkWord(string word);
    bool humanWordSearch(string word);
    Set<string> computerWordSearch();
    int getScoreHuman();
    int getScoreComputer();
    void printBoard();
    void printComputer();

    // TODO: add any other member functions/variables necessary
    friend ostream& operator<<(ostream& out, Boggle& boggle);

private:
    // TODO: add any other member functions/variables necessary
    Lexicon *dictionary_ptr;
    Grid<char> board = Grid<char>(4, 4);
    Grid<bool> visited = Grid<bool>(4, 4, false);
    Set<string> human_word;
    Set<string> computer_word;
    int human_score = 0;
    int computer_score = 0;

    bool searchWord_helper(string word, int r, int c);
    void computerSearch_helper(string word, int r, int c);
};

#endif // _boggle_h
