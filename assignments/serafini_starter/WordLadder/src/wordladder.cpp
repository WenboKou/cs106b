// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "lexicon.h"
#include "queue.h"
#include "simpio.h"

using namespace std;

void printLadder(Stack<string>& ladder) {
    while (!ladder.isEmpty()) {
        cout << ladder.pop() << " ";
    }
    cout << endl;
}

int main() {
    // TODO: Finish the program!
    Lexicon dictionary;
    ifstream stream;
    string filename = promptUserForFile(stream, "Dictionary file name?");
    //string filename = getLine("Dictionary file name?");
    dictionary = Lexicon(filename);
    while (1) {
        cout << endl;
        string word1 = getLine("Word #1 (or Enter to quit)");
        if (word1 == "") {
            break;
        }
        string word2 = getLine("Word #2 (or Enter to quit)");
        if (word2 == "") {
            break;
        }
        if (word1.length() != word2.length()) {
            cout << "two words must be the same length." << endl;
            continue;
        }
        word1 = toLowerCase(word1);
        word2 = toLowerCase(word2);
        if (!dictionary.contains(word1) || !dictionary.contains(word2)) {
            cout << "The two words must be found in the dictionary." << endl;
        }
        if (word1 == word2) {
            cout << "The two words must be different." << endl;
        }

        Lexicon exist_words;
        Queue<Stack<string>> ladders;
        Stack<string> ladder;
        string word;

        ladder.push(word1);
        ladders.enqueue(ladder);
        exist_words.add(word1);
        while (!ladders.isEmpty()) {
            ladder = ladders.dequeue();
            int word_len = ladder.peek().length();
            for (int i = 0; i < word_len; i++) {
                word = ladder.peek();
                for (char c = 'a'; c <= 'z'; c++) {
                    word[i] = c;
                    //cout << "c: " << c << "  word: " << word << endl;
                    if (!dictionary.contains(word)) {continue;}
                    Stack<string> ladder_copy = ladder;
                    if (!exist_words.contains(word)) {
                        ladder_copy.push(word);
                        if (word == word2) {
                            ladders.clear();
                            word = "";
                            printLadder(ladder_copy);
                            break;
                        } else {
                            ladders.enqueue(ladder_copy);
                            exist_words.add(word);
                        }
                    }
                }
            }
        }
    }

    cout << "Have a nice day." << endl;
    return 0;
}
