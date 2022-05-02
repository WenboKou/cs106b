// This is a .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "Boggle.h"

// letters on all 6 sides of every cube
static string CUBES[16] = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

// letters on every cube in 5x5 "Big Boggle" version (extension)
static string BIG_BOGGLE_CUBES[25] = {
   "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
   "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
   "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
   "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
   "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

void Boggle::printBoard() {
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            cout <<board[r][c];
        }
        cout << endl;
    }
    cout << endl;
    cout << "Your words (" << human_word.size() << "): " << human_word << endl;
    cout << "Your score: " << human_score << endl;
}

void Boggle::printComputer() {
    cout << endl;
    cout << "My words (" << computer_word.size() << "): " << computer_word << endl;
    cout << "My score: " << computer_score << endl;
    if (computer_score > human_score) {
        cout << "You lose the game!" << endl;
    } else {
        cout << "You win the game!" << endl;
    }
}

Boggle::Boggle(Lexicon& dictionary, string boardText) {
    // TODO: implement
    this->dictionary_ptr = &dictionary;
    //board.resize(4, 4);
    // first choice: randomly set the board;
    if (boardText.empty()) {
        Vector<int> v = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
        shuffle(v);
        for (int r = 0; r < 4; r++) {
            for (int c = 0; c < 4; c++) {
                board[r][c] = CUBES[v[r*4+c]][randomInteger(0, 5)];
            }
        }
    } else {
        // second choice: boardText setting;
        cout << "boardText: " << boardText << endl;
        for (int r = 0; r < 4; r++) {
            for (int c = 0; c < 4; c++) {
                board[r][c] = toupper(boardText[r*4+c]);
            }
        }
    }
}

char Boggle::getLetter(int row, int col) {
    // TODO: implement
    if (row >= 4 || row < 0 || col >= 4 || col < 0) {
        throw "row and/or column are out of bounds.";
    }
    return board[row][col];
}

bool Boggle::checkWord(string word) {
    // TODO: implement
    if (word.length() < 4) {
        return false;
    }
    word = toUpperCase(word);
    //check if the word has already been used.
    if (human_word.contains(word) || computer_word.contains(word)) {
        return false;
    }
    if (!dictionary_ptr->contains(word)) {
        return false;
    }
    return true;
}

bool Boggle::searchWord_helper(string word, int r, int c) {
    if (word.length() == 0) {
        return true;
    }
    if (r >= 4 || r < 0 || c >= 4 || c < 0) {
        return false;
    }
    if (visited[r][c]) {
        return false;
    }
    if (board[r][c] == word[0]) {
        visited[r][c] = true;
        string subword = word.substr(1);
        if (searchWord_helper(subword, r-1, c-1)) {
            visited[r][c] = false;
            return true;
        } else if (searchWord_helper(subword, r-1, c)) {
            visited[r][c] = false;
            return true;
        } else if (searchWord_helper(subword, r-1, c+1)) {
            visited[r][c] = false;
            return true;
        }  else if (searchWord_helper(subword, r, c-1)) {
            visited[r][c] = false;
            return true;
        } else if (searchWord_helper(subword, r, c+1)) {
            visited[r][c] = false;
            return true;
        } else if (searchWord_helper(subword, r+1, c-1)) {
            visited[r][c] = false;
            return true;
        } else if (searchWord_helper(subword, r+1, c)) {
            visited[r][c] = false;
            return true;
        } else if (searchWord_helper(subword, r+1, c+1)) {
            visited[r][c] = false;
            return true;
        } else {
            visited[r][c] = false;
            return false;
        }
    } else {
        return false;
    }
}

bool Boggle::humanWordSearch(string word) {
    // TODO: implement
    word = toUpperCase(word);
    if (checkWord(word)) {
        for (int r = 0; r < 4; r++) {
            for (int c = 0; c < 4; c++) {
                if (searchWord_helper(word, r, c)) {
                    human_word.add(word);
                    human_score += (word.length() - 3);
                    return true;
                }
            }
        }
    }
    return false;   // remove this
}

int Boggle::getScoreHuman() {
    // TODO: implement
    return human_score;   // remove this
}

void Boggle::computerSearch_helper(string word, int r, int c) {
    if (r >= 4 || r < 0 || c >= 4 || c < 0) {
        return;
    }
    if (visited[r][c]) {
        return;
    }
    word += board[r][c];
    if (!dictionary_ptr->containsPrefix(word)) {
        return;
    }
    if (dictionary_ptr->contains(word)) {
        if (!human_word.contains(word) & !computer_word.contains(word) & word.length() >= 4) {
            computer_word.add(word);
            computer_score += (word.length() - 3);
        }
    }
    visited[r][c] = true;
    computerSearch_helper(word, r-1, c-1);
    computerSearch_helper(word, r-1, c);
    computerSearch_helper(word, r-1, c+1);
    computerSearch_helper(word, r, c-1);
    computerSearch_helper(word, r, c+1);
    computerSearch_helper(word, r+1, c-1);
    computerSearch_helper(word, r+1, c);
    computerSearch_helper(word, r+1, c+1);
    visited[r][c] = false;
    return;
}

Set<string> Boggle::computerWordSearch() {
    // TODO: implement
    for (int r = 0; r < 4; r ++) {
        for (int c = 0; c < 4; c++) {
            computerSearch_helper("", r, c);
        }
    }
    return computer_word;
}

int Boggle::getScoreComputer() {
    // TODO: implement
    return computer_score;   // remove this
}

ostream& operator<<(ostream& out, Boggle& boggle) {
    // TODO: implement
    return out;
}
