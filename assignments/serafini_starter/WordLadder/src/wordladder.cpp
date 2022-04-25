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
    string filename = getLine("Dictionary file name?");
    string word1 = getLine("Word #1 (or Enter to quit)");
    if (word1 == "") {
        cout << "Have a nice day!" << endl;
        return 0;
    }
    string word2 = getLine("Word #2 (or Enter to quit)");
    if (word2 == "") {
        cout << "Have a nice day!" << endl;
        return 0;
    }
    cout << "word1" << word1 << endl;
    cout << "word2" << word2 << endl;

    Lexicon dictionary;
    Lexicon exist_words;
    dictionary = Lexicon(filename);
    Queue<Stack<string>> ladders;
    Stack<string> ladder;
    string word;

    ladder.push(word1);
    ladders.enqueue(ladder);
    while (!ladders.isEmpty()) {
        ladder = ladders.dequeue();
        word = ladder.peek();
        for (int i = 0; i < word.length(); i++) {
            for (char c = 'a'; c < 'z'; c++) {
                word[i] = c;
                if (!dictionary.contains(word)) {continue;}
                Stack<string> ladder_copy = ladder;
                if (!exist_words.contains(word)) {
                    ladder_copy.push(word);
                    if (word == word2) {
                        ladders.clear();
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



    cout << "Have a nice day." << endl;
    return 0;
}
