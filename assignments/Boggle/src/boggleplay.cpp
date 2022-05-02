// This is a .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "Boggle.h"
#include "lexicon.h"
#include "simpio.h"
#include "console.h"

using namespace std;

bool check_boardText(string& boardText) {
    int text_length = boardText.length();
    if (text_length != 16) {
        return false;
    }
    for (char c : boardText) {
        c = toupper(c);
        if ('A' > c || c > 'Z') {
            return false;
        }
    }
    return true;
}

void playOneGame(Lexicon& dictionary) {
    // TODO: implement
    string boardText;
    Boggle game(dictionary, "");
    if (!getYesOrNo("Do you want to generate a random board? (Y/N)? ")) {
        boardText = getLine("Type the 16 letters to appear on the board: ");
        while (!check_boardText(boardText)) {
            cout << "That is not a valid 16-letter board string. Try again." << endl;
            boardText = getLine("Type the 16 letters to appear on the board: ");
        }
        Boggle game_round(dictionary, boardText);
        game = game_round;
    }
    clearConsole();
    cout << "It's your turn!" << endl;
    game.printBoard();

    string word = getLine("Type a word (or Enter to stop): ");
    while (!word.empty()) {
        if (game.checkWord(word)) {
            if (game.humanWordSearch(word)) {
                clearConsole();
                cout << "You found a new word! " << toUpperCase(word) << endl;;
                game.printBoard();
            } else {
                clearConsole();
                cout << "That word can't be formed on this board." << endl;
                game.printBoard();
            }
        } else {
            clearConsole();
            cout << "You must enter an unfound 4+ letter word from the dictionary." << endl;
            game.printBoard();
        }
        word = getLine("Type a word (or Enter to stop): ");
    }
    // computer's turn.
    cout << endl;
    cout << "It's my turn!" << endl;
    game.computerWordSearch();
    game.printComputer();
}
